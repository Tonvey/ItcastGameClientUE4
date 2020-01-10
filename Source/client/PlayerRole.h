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
    DECLARE_EVENT_OneParam(APlayerRole, OnSetPid,int);
    DECLARE_EVENT_OneParam(APlayerRole, OnSetPlayerName,FString);
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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int mPid = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString mPlayerName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ATextRender *mPlayerNameTextRender;
};
