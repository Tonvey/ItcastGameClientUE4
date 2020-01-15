// Fill out your copyright notice in the Description page of Project Settings.


#include "CompetitorRole.h"
#include "GameEventDispatcher.h"
#include "DataAdapter.h"

ACompetitorRole::ACompetitorRole()
{
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&ACompetitorRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&ACompetitorRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &ACompetitorRole::SetPosition);
}

ACompetitorRole::~ACompetitorRole()
{
}

void ACompetitorRole::SetPosition(int _pid, pb::Position _pos)
{
    if (_pid != this->mPid)
        return;
    auto location = DataAdapter::PostionSC(_pos);
    UE_LOG(LogTemp, Display, TEXT("ACompetitorRole::SetPosition x:%f y:%f z:%f"),location.X,location.Y,location.Z);
    this->SetActorLocation(location);
    FQuat rot = FQuat::MakeFromEuler(FVector(0, 0, _pos.v()));
    this->SetActorRotation(rot);
}
