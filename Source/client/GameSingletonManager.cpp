// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSingletonManager.h"
#include "Engine.h"

UGameSingletonManager *UGameSingletonManager::smInstance=nullptr;
UGameSingletonManager *UGameSingletonManager::GetInstance()
{
    if (smInstance == nullptr)
    {
		smInstance = Cast<UGameSingletonManager>(GEngine->GameSingleton);
    }
    return smInstance;
}
UGameSingletonManager::UGameSingletonManager()
{
    UE_LOG(LogTemp, Display, TEXT("UGameSingletonManager::UGameSingletonManager()"));
}

UGameSingletonManager::~UGameSingletonManager()
{
    UE_LOG(LogTemp, Display, TEXT("UGameSingletonManager::~UGameSingletonManager()"));
}
