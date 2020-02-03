// Fill out your copyright notice in the Description page of Project Settings.


#include "clientGameModeBase.h"
#include "NetworkController.h"
#include "GameEventDispatcher.h"
#include "CompetitorRole.h"
#include "DataAdapter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "NetworkMessageFactoryUtil.h"
#include "Engine.h"
AclientGameModeBase* AclientGameModeBase::smCurrentMode=nullptr;
AclientGameModeBase::AclientGameModeBase()
    :isChangingLevel(false)
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::AclientGameModeBase") );
    smCurrentMode = this;
    PrimaryActorTick.bCanEverTick = true;
    //TODO 以下代码也可行  ,也可以直接在blueprint编辑器上直接设置该值
    //static ConstructorHelpers::FObjectFinder<UBlueprint> PutNameHere(TEXT("Blueprint'/Game/BluePrints/Competitor.Competitor'"));  
    //if (PutNameHere.Object)   
    //{  
    //    CompetitorClass = (UClass*)PutNameHere.Object->GeneratedClass;  
    //}  
    levelNameArray.Add(FName("Undefined"));
    levelNameArray.Add(FName("WorldMap"));
    levelNameArray.Add(FName("BattleField"));
}
AclientGameModeBase::~AclientGameModeBase()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::~AclientGameModeBase"));
    if (!isChangingLevel)
    {
        UNetworkController::GetInstance()->Reset();
    }
    UGameEventDispatcher::GetInstance().Reset();
    mPlayerMap.Reset();
}
ACompetitorRole* AclientGameModeBase::CreateACompetitorToLevel_Implementation(int _pid,
    const FString& _name,
    FVector _groundLocation,
    FRotator _rotation,
    int _hp)
{
    auto newRole = this->GetWorld()->SpawnActor<ACompetitorRole>(
        CompetitorClass->GetDefaultObject()->GetClass(),
        _groundLocation,
        _rotation
        );
    if (newRole == nullptr)
    {
		UE_LOG(LogTemp, Error, TEXT("AclientGameModeBase::CreateAcompetitorToLevel_Implementation fail"));
        assert(false);
    }
    newRole->SetPid(_pid);
    newRole->SetPlayerName(_name);
    newRole->SetHP(_hp);
    newRole->SetPlayerGroundLocation(_groundLocation);
    newRole->GetOnLogoff().AddUObject(this, &AclientGameModeBase::OnPlayerLogoff);
    return newRole;
}
void AclientGameModeBase::ChangeLevel(int _srcId, int _targetId)
{
    if (_targetId > levelNameArray.Num() - 1 || _targetId <= 0)
    {
        //TODO : LOG
        return;
    }
    //TODO : 切换关卡
    UGameplayStatics::OpenLevel(GetWorld(), levelNameArray[_targetId]);
}
void AclientGameModeBase::PreChangeLevel()
{
    isChangingLevel = true;
}
void AclientGameModeBase::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    UNetworkController::GetInstance()->ProcessNetworkMessage();
}

void AclientGameModeBase::OnNewPlayer(int _pid, std::string _name,pb::Position _pos)
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::OnNewPlayer") );
	if (mPlayerMap.Contains(_pid))
	{
		UE_LOG(LogTemp, Error, TEXT("AclientGameModeBase::OnNewPlayer duplicate player"));
        return;
	}
    FVector location = DataAdapter::PostionSC(_pos);
    FRotator rot = FRotator::MakeFromEuler(FVector(0, 0, _pos.v()));
    auto role = this->CreateACompetitorToLevel(_pid, UTF8_TO_TCHAR(_name.c_str()), location, rot,_pos.bloodvalue());
    if (role != nullptr)
    {
		UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::OnNewPlayer pid is : %d"), role->GetPid());
        this->RegisterPlayer(_pid, role);
    }
    else
    {
		UE_LOG(LogTemp, Error, TEXT("AclientGameModeBase::OnNewPlayer failed"));
        assert(false);
    }
}
void AclientGameModeBase::OnSyncMainPlayerId(APlayerRole *mainPlayer , int _pid)
{
    //auto a = *mainPlayer;
    //TODO : 继承自 UObject的对象不能被拷贝和移动
    if (mMainPlayer != mainPlayer)
    {
        if (mMainPlayer != nullptr)
        {
            this->UnregisterPlayer(mMainPlayer->GetPid());
        }
        this->mMainPlayer = mainPlayer;
        this->RegisterPlayer(_pid, mainPlayer);
    }
}
void AclientGameModeBase::OnChangeWorld(int _srcId, int _targetId, int _res)
{
    if (_res == 1)
    {
        if (_targetId != currentLevelID)
        {
			UNetworkController::GetInstance()->PauseProcessMessage();
			this->PreChangeLevel();
			this->ChangeLevel(_srcId, _targetId);
        }
        else
        {
            //TODO 打Log
        }
    }
}
void AclientGameModeBase::OnPlayerLogoff(int _pid)
{
    this->UnregisterPlayer(_pid);
}
void AclientGameModeBase::RegisterPlayer(int _pid, APlayerBase* _player)
{
    if (mPlayerMap.Contains(_pid))
    {
		UE_LOG(LogTemp, Error, TEXT("AclientGameModeBase::RegisterPlayer duplicate player"));
    }
    else
    {
		mPlayerMap.Add(_pid, _player);
    }
}
void AclientGameModeBase::UnregisterPlayer(int _pid)
{
    mPlayerMap.Remove(_pid);
}

void AclientGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::BeginPlay()"));
    UNetworkController::GetInstance()->Init(TEXT("127.0.0.1"),8899);
    UNetworkController::GetInstance()->ResumeProcessMessage();
    UGameEventDispatcher::GetInstance().Init();
    UGameEventDispatcher::GetInstance().GetOnNewPlayer().AddUObject(this, &AclientGameModeBase::OnNewPlayer);
    UGameEventDispatcher::GetInstance().GetOnMainPlayerSync().AddUObject(this, &AclientGameModeBase::OnSyncMainPlayerId);
    UGameEventDispatcher::GetInstance().GetOnChangeWorld().AddUObject(this, &AclientGameModeBase::OnChangeWorld);
}

void AclientGameModeBase::Reset()
{
    Super::Reset();
}

void AclientGameModeBase::BeginDestroy()
{
    Super::BeginDestroy();
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::BeginDestroy") );
    if (!isChangingLevel)
    {
		UNetworkController::GetInstance()->Finish();
    }
    UGameEventDispatcher::GetInstance().Reset();
    mPlayerMap.Reset();
}

void AclientGameModeBase::RequestChangeWorld(int _pid, int _target)
{
    auto msg = UNetworkMessageFactoryUtil::MakeChangeWorldRequest(_pid, this->mWorldId, _target);
    UNetworkController::GetInstance()->PushMsg(msg);
}

