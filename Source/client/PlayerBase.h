// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "GameEventDispatcher.h"
#include "PlayerBase.generated.h"

UCLASS()
class CLIENT_API APlayerBase : public ACharacter
{
	GENERATED_BODY()
    DECLARE_MY_EVENT_MEMBER_OneParam(APlayerBase,OnSetPid,int);
    DECLARE_MY_EVENT_MEMBER_OneParam(APlayerBase,OnSetPlayerName,FString);

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
    virtual void SetPid(int _pid);

    virtual void SetPlayerName(std::string _playerName);

    UFUNCTION(BlueprintCallable)
    virtual void SetPlayerName(FString _playerName);

    virtual void SetPosition(int _pid,pb::Position _pos);
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
