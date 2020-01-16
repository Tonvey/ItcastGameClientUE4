// Fill out your copyright notice in the Description page of Project Settings.


#include "clientGameModeBase.h"
#include "NetworkController.h"
#include "GameEventDispatcher.h"
#include "CompetitorRole.h"
AclientGameModeBase* AclientGameModeBase::smCurrentMode=nullptr;
AclientGameModeBase::AclientGameModeBase()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::AclientGameModeBase") );
    smCurrentMode = this;
    PrimaryActorTick.bCanEverTick = true;
}
AclientGameModeBase::~AclientGameModeBase()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::~AclientGameModeBase") );
    NetworkController::GetInstance().Reset();
    mPlayerMap.Reset();
    if (mMainPlayer != nullptr)
    {
        UnregisterMainPlayer(mMainPlayer);
    }
    if (mNewPlayerHandle.IsValid())
    {
        GameEventDispatcher::GetInstance().GetOnNewPlayer().Remove(mNewPlayerHandle);
    }
}
void AclientGameModeBase::Init()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::Init") );
    NetworkController::GetInstance().Init(TEXT("127.0.0.1"),8899);
    UE_LOG(LogTemp, Display, TEXT("hahahahaha") );
    GameEventDispatcher::GetInstance().Init();
    this->mNewPlayerHandle = GameEventDispatcher::GetInstance().GetOnNewPlayer().AddUObject(this, &AclientGameModeBase::OnNewPlayer);
}
void AclientGameModeBase::BeginPlay()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::BeginPlay") );
    Super::BeginPlay();
}
void AclientGameModeBase::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    NetworkController::GetInstance().ProcessNetworkMessage();
}

void AclientGameModeBase::OnNewPlayer(int _pid, std::string _name)
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::OnNewPlayer") );
	if (mPlayerMap.Contains(_pid))
	{
		UE_LOG(LogTemp, Error, TEXT("AclientGameModeBase::OnNewPlayer duplicate player"));
        return;
	}
    auto role = this->CreateACompetitorToLevel(_pid, UTF8_TO_TCHAR(_name.c_str()));
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
void AclientGameModeBase::OnSyncMainPlayerId(int _pid)
{
    this->RegisterPlayer(_pid, mMainPlayer);
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
void AclientGameModeBase::RegisterMainPlayer(APlayerRole* mainPlayer)
{
    if (mMainPlayer != nullptr)
    {
        UnregisterMainPlayer(mMainPlayer);
    }
    mMainPlayer = mainPlayer;
    this->mainPlayerSetPidHandle = mMainPlayer->GetOnSetPid().AddUObject(this, &AclientGameModeBase::OnSyncMainPlayerId);
}

void AclientGameModeBase::UnregisterMainPlayer(APlayerRole* mainPlayer)
{
    //TODO remove from event ....
    mMainPlayer->GetOnSetPid().Remove(mainPlayerSetPidHandle);
    mMainPlayer = nullptr;
}
