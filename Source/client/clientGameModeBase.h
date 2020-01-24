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
    ACompetitorRole *CreateACompetitorToLevel(int _pid ,const FString &_name , FVector _groundLocation,FRotator _rotation,int _hp);
    ACompetitorRole *CreateACompetitorToLevel_Implementation(int _pid ,const FString &_name , FVector _groundLocation,FRotator _rotation,int _hp);
    UFUNCTION(BlueprintImplementableEvent)
    void ChangeWorld(int _srcId ,int _targetId);
    UFUNCTION(BlueprintCallable, Category = "Action")
    virtual void Init();
    virtual void BeginPlay()override;
    virtual void Tick(float deltaTime) override;
    virtual void OnNewPlayer(int _pid, std::string _name,pb::Position _pos);
    virtual void OnSyncMainPlayerId(APlayerRole* mainPlayer, int _pid);
    virtual void OnChangeWorld(int _srcId, int _targetId, int _res);
    virtual void OnPlayerLogoff(int _pid);
    virtual void RegisterPlayer(int _pid ,APlayerBase *_player);
    virtual void UnregisterPlayer(int _pid);
    static AclientGameModeBase &GetCurrentClientGameMode(){ return *smCurrentMode; }

	UFUNCTION(BlueprintCallable)
    void RequestChangeWorld(int _pid,int _target);
    UPROPERTY( BlueprintReadWrite )
	TSubclassOf<ACompetitorRole> CompetitorClass;
    UPROPERTY( BlueprintReadOnly )
    APlayerRole *mMainPlayer;

private:
	TSharedPtr<GameMsg> MakeChangeWorldRequest(int _pid, int _src,int _target);
protected:
    TMap<int, APlayerBase*> mPlayerMap;
    static AclientGameModeBase* smCurrentMode;
    UPROPERTY(BlueprintReadWrite)
	int mWorldId;
};
