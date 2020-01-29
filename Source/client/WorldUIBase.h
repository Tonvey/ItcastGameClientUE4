// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldUIBase.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UWorldUIBase : public UUserWidget
{
	GENERATED_BODY()
public:	
	UWorldUIBase(const FObjectInitializer& ObjectInitializer);
	~UWorldUIBase();
	UFUNCTION(BlueprintImplementableEvent, Category = "Cpp_Event")
	void OnNewChatMessage(int pid, const FString& name, const FString& content);
	virtual bool Initialize()override;
	virtual void BeginDestroy() override;
private:
	FDelegateHandle mHandler;
};
