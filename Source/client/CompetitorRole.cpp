// Fill out your copyright notice in the Description page of Project Settings.


#include "CompetitorRole.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameEventDispatcher.h"
#include "DataAdapter.h"

ACompetitorRole::ACompetitorRole()
{
    UE_LOG(LogTemp, Display, TEXT("ACompetitorRole::ACompetitorRole create"));
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &ACompetitorRole::SetPlayerGroundLocation);
    GameEventDispatcher::GetInstance().GetOnPlayerLogoff().AddUObject(this,&ACompetitorRole::OnLogoff);
	PrimaryActorTick.bCanEverTick = true;

    //TODO: 这是解决对象不运动的关键
    auto comp = this->GetCharacterMovement();
    comp->bRunPhysicsWithNoController = true;
}

ACompetitorRole::~ACompetitorRole()
{
    mOnLogoff.Broadcast(this->mPid);
    mOnLogoff.Clear();
}

void ACompetitorRole::SetPlayerGroundLocation(int _pid, pb::Position _pos)
{
    if (_pid != mPid)
    {
        return;
    }
    auto location = DataAdapter::PostionSC(_pos);
    this->HP = _pos.bloodvalue();
    this->SyncGroundPositionTo(location, _pos.v());
}

void ACompetitorRole::SetPlayerGroundLocation(const FVector& _pos)
{
    Super::SetPlayerGroundLocation(_pos);
}

void ACompetitorRole::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACompetitorRole::OnLogoff(int _pid)
{
    if (mPid != _pid)
    {
        return;
    }
    Destroy(this);
    mOnLogoff.Broadcast(this->mPid);
    mOnLogoff.Clear();
}

