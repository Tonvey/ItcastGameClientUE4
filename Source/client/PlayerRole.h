// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include <string>
#include "GameEventDispatcher.h"
#include "Components/TextRenderComponent.h"
#include "PlayerRole.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API APlayerRole : public APlayerBase
{
	GENERATED_BODY()
    DECLARE_MULTICAST_DELEGATE_OneParam(OnSetPid,int);
    DECLARE_MULTICAST_DELEGATE_OneParam(OnSetPlayerName,FString);
    DECLARE_EVENT_MEMBER_INSTANCE(OnSetPid);
    DECLARE_EVENT_MEMBER_INSTANCE(OnSetPlayerName);
public:
    APlayerRole();
    ~APlayerRole();
    int Pid()const
    {
        return mPid;
    }
    FString PlayerName()const
    {
        return mPlayerName;
    }
    UFUNCTION(BlueprintCallable)
    void SetPid(int _pid);
    UFUNCTION(BlueprintCallable)
    void SetPlayerName(FString _playerName);
    void SetPlayerName(std::string _playerName);
    void SetPosition(int _pid,pb::Position _pos);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int mPid = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int HP = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString mPlayerName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* mPlayerNameTextComp;
};
