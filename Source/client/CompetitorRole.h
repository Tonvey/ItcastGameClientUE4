// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "GameEventDispatcher.h"
#include "CompetitorRole.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API ACompetitorRole : public APlayerBase
{
	GENERATED_BODY()
    DECLARE_MY_EVENT_MEMBER_OneParam(ACompetitorRole,OnLogoff,int);
public:
	ACompetitorRole();
	~ACompetitorRole();
	void OnLogoff(int _pid);
	void OnSkillTrigger(int pid,int skillId,int bulletId,const pb::Position &triggerPos,const pb::Velocity &bulletVelocity);
	UFUNCTION(BlueprintImplementableEvent, Category = "Cpp_Event")
	void ReceiveSkillTrigger(int skillId , int bulletId ,const FVector skillPos, const FVector &bulletVelocity);
    virtual void Init()override;
    virtual void SetPlayerGroundLocation(int _pid,pb::Position _pos) override;
    virtual void SetPlayerGroundLocation(const FVector &_pos)override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Cpp_Event")
    void SyncGroundPositionTo(FVector _destination, float _direction);
	virtual void Tick(float DeltaTime) override;
};
