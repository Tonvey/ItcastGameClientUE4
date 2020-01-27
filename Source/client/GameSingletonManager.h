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
	static UGameSingletonManager *GetInstance();
	UGameSingletonManager();
	~UGameSingletonManager();
public:
	UNetworkController *GetNetworkController()
	{
		if (networkController == nullptr)
		{
			networkController = NewObject<UNetworkController>();
		}
		return networkController;
	}
	UGameEventDispatcher *GetGameEventDispatcher()
	{
		if (gameEventDispatcher == nullptr)
		{
			gameEventDispatcher = NewObject<UGameEventDispatcher>();
		}
		return gameEventDispatcher;
	}
private:
	UPROPERTY()
	UNetworkController *networkController;
	UPROPERTY()
	UGameEventDispatcher *gameEventDispatcher;
private:
	static UGameSingletonManager* smInstance;
};
