// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkConnector.h"
#include "GameEventDispatcher.h"
#include "clientGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class CLIENT_API AclientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    AclientGameModeBase();
    ~AclientGameModeBase();
    UFUNCTION(BlueprintCallable, Category = "Action")
    virtual void Init();
    virtual void BeginPlay()override;
    virtual void Tick(float deltaTime) override;
    virtual void OnNewPlayer(int _pid, std::string _name);
private:
    NetworkConnector *mConnector;
};
