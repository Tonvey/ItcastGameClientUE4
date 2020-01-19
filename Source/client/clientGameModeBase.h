// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkConnector.h"
#include "GameEventDispatcher.h"
#include "CompetitorRole.h"
#include "PlayerRole.h"
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
    UFUNCTION(BlueprintNativeEvent)
    ACompetitorRole *CreateACompetitorToLevel(int _pid ,const FString &_name , FVector _groundLocation,FRotator _rotation);
    ACompetitorRole *CreateACompetitorToLevel_Implementation(int _pid ,const FString &_name , FVector _groundLocation,FRotator _rotation);
    UFUNCTION(BlueprintCallable, Category = "Action")
    virtual void Init();
    virtual void BeginPlay()override;
    virtual void Tick(float deltaTime) override;
    virtual void OnNewPlayer(int _pid, std::string _name,pb::Position _pos);
    virtual void OnSyncMainPlayerId(APlayerRole* mainPlayer, int _pid);
    virtual void OnPlayerLogoff(int _pid);
    virtual void RegisterPlayer(int _pid ,APlayerBase *_player);
    virtual void UnregisterPlayer(int _pid);
    static AclientGameModeBase &GetCurrentClientGameMode(){ return *smCurrentMode; }

    UPROPERTY( BlueprintReadWrite )
	TSubclassOf<ACompetitorRole> CompetitorClass;
protected:
    TMap<int, APlayerBase*> mPlayerMap;
    static AclientGameModeBase* smCurrentMode;
    APlayerRole *mMainPlayer;
    FDelegateHandle mMainPlayerSyncHandle;
    FDelegateHandle mNewPlayerHandle;
    FDelegateHandle mMainPlayerLogoffHandle;
};
