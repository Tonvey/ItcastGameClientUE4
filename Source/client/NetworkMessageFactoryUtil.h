// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameMsg.h"
#include "NetworkController.h"
#include "GameEventDispatcher.h"
#include "NetworkMessageFactoryUtil.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UNetworkMessageFactoryUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable)
	static UNetworkController *GetNetworkControllerInstance();
    UFUNCTION(BlueprintCallable)
	static UGameEventDispatcher *GetGameEventDispatcher();
    UFUNCTION(BlueprintCallable)
	static FGameSingleTLV MakeTalkContent(const FText &_content);
    UFUNCTION(BlueprintCallable)
    static FGameSingleTLV MakeSyncPosition(const FGameMsgPack &_pb_position);
    UFUNCTION(BlueprintCallable)
	static FGameSingleTLV MakeChangeWorldRequest(int _pid, int _src,int _target);
	
    UFUNCTION(BlueprintCallable)
    static FGameSingleTLV MakeSkillTrigger(int pid, int skillId,int bulletId,const FGameMsgPack &position , const FGameMsgPack &velocity);
};
