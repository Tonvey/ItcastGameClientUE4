// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"
#include "DataAdapter.h"

APlayerRole::APlayerRole()
{
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&APlayerRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&APlayerRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &APlayerRole::SetPlayerGroundLocation);
}
APlayerRole::~APlayerRole()
{
}

void APlayerRole::SetPid(int _pid)
{
    Super::SetPid(_pid);
    GameEventDispatcher::GetInstance().GetOnMainPlayerSync().Broadcast(this, _pid);
}

