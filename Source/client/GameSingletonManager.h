// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkController.h"
#include "GameEventDispatcher.h"
#include "GameSingletonManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CLIENT_API UGameSingletonManager : public UObject
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
	static UGameSingletonManager *GetInstance();
	UGameSingletonManager();
	~UGameSingletonManager();
public:
    UFUNCTION(BlueprintCallable)
	UNetworkController *GetNetworkController()
	{
		//if (networkController == nullptr)
		//{
		//	networkController = NewObject<UNetworkController>();
		//}
		if (networkController->IsPendingKill())
		{
			return nullptr;
		}
		return networkController;
	}
    UFUNCTION(BlueprintCallable)
	UGameEventDispatcher *GetGameEventDispatcher()
	{
		//if (gameEventDispatcher == nullptr)
		//{
		//	gameEventDispatcher = NewObject<UGameEventDispatcher>();
		//}
		if (gameEventDispatcher->IsPendingKill())
		{
			return nullptr;
		}
		return gameEventDispatcher;
	}
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    FString ServerIP = "127.0.0.1";
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    int32 ServerPort = 8899;
private:
	UPROPERTY()
	UNetworkController *networkController;
	UPROPERTY()
	UGameEventDispatcher *gameEventDispatcher;
private:
	static UGameSingletonManager* smInstance;
};
