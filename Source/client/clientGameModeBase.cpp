// Fill out your copyright notice in the Description page of Project Settings.


#include "clientGameModeBase.h"
#include "NetworkController.h"
#include "GameEventDispatcher.h"
#include "CompetitorRole.h"
AclientGameModeBase::AclientGameModeBase()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::AclientGameModeBase") );
    PrimaryActorTick.bCanEverTick = true;
}
AclientGameModeBase::~AclientGameModeBase()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::~AclientGameModeBase") );
    if(mConnector!=nullptr)
    {
        delete mConnector;
    }
}
void AclientGameModeBase::Init()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::Init") );
    NetworkController::GetInstance().Init(TEXT("127.0.0.1"),8899);
    UE_LOG(LogTemp, Display, TEXT("hahahahaha") );
    GameEventDispatcher::GetInstance().Init();
    GameEventDispatcher::GetInstance().GetOnNewPlayer().AddUObject(this, &AclientGameModeBase::OnNewPlayer);
}
void AclientGameModeBase::BeginPlay()
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::BeginPlay") );
    Super::BeginPlay();
    Init();
}
void AclientGameModeBase::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    NetworkController::GetInstance().ProcessNetworkMessage();
}

void AclientGameModeBase::OnNewPlayer(int _pid, std::string _name)
{
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::OnNewPlayer") );
    auto role = NewObject<ACompetitorRole>();
}
