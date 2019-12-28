// Fill out your copyright notice in the Description page of Project Settings.


#include "clientGameModeBase.h"
AclientGameModeBase::AclientGameModeBase()
{
    mConnector=new NetworkConnector;
    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::AclientGameModeBase") );
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
    mConnector->Init();
}
//void AclientGameModeBase::BeginPlay()
//{
//    UE_LOG(LogTemp, Display, TEXT("AclientGameModeBase::BeginPlay") );
//    Super::BeginPlay();
//    Init();
//}
