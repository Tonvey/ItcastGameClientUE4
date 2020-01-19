// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "CompetitorRole.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API ACompetitorRole : public APlayerBase
{
	GENERATED_BODY()
public:
	ACompetitorRole();
	~ACompetitorRole();
	void OnLogoff(int _pid);
    virtual void SetPlayerGroundLocation(int _pid,pb::Position _pos) override;
    virtual void SetPlayerGroundLocation(const FVector &_pos)override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Cpp_Event")
    void SyncGroundPositionTo(FVector _destination, float _direction);
	virtual void Tick(float DeltaTime) override;
};
