// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatCenter.h"
#include "WorldChatCenter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CLIENT_API UWorldChatCenter : public UObject , public  IChatCenter
{
	GENERATED_BODY()
	//IMPLEMENT_CLASS(UWorldChatCenter, IChatCenter)
public:
	UWorldChatCenter();
	~UWorldChatCenter();
	virtual void SendContent_Implementation(const FText &content)override;
};
