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
    virtual void SetPosition(int _pid,pb::Position _pos) override;
};
