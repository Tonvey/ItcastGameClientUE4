// Fill out your copyright notice in the Description page of Project Settings.


#include "CompetitorRole.h"
#include "GameEventDispatcher.h"
#include "DataAdapter.h"

ACompetitorRole::ACompetitorRole()
{
    UE_LOG(LogTemp, Display, TEXT("ACompetitorRole::ACompetitorRole create"));
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&ACompetitorRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&ACompetitorRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &ACompetitorRole::SetPosition);
    GameEventDispatcher::GetInstance().GetOnPlayerLogoff().AddUObject(this,&ACompetitorRole::OnLogoff);
}

ACompetitorRole::~ACompetitorRole()
{
}

void ACompetitorRole::OnLogoff(int _pid)
{
    if (mPid != _pid)
    {
        return;
    }
    Destroy(this);
}

