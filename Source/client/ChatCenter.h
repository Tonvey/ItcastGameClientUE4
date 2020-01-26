// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChatCenter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UChatCenter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLIENT_API IChatCenter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SendContent(const FText &content);
	virtual void SendContent_Implementation(const FText &content);
};
