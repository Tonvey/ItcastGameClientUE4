// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include <string>
#include "PlayerRole.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API APlayerRole : public APlayerBase
{
	GENERATED_BODY()
public:
    APlayerRole();
    ~APlayerRole();
    virtual void SetPid(int _pid) override;
    virtual void Tick(float DeltaTime) override;
private:
    float mLastPositionSyncInterval;
    FVector4 mLastSyncPosition;
};
