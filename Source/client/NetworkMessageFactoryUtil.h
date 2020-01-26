// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameMsg.h"
#include "NetworkMessageFactoryUtil.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UNetworkMessageFactoryUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static GameSingleTLV MakeTalkContent(const FText &_content);
    static GameSingleTLV MakeSyncPosition(pb::Position &_posistion);
	static GameSingleTLV MakeChangeWorldRequest(int _pid, int _src,int _target);
	
};
