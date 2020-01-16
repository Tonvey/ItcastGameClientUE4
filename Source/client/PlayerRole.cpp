// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"
#include "clientGameModeBase.h"
#include "DataAdapter.h"

APlayerRole::APlayerRole()
{
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&APlayerRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&APlayerRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &APlayerRole::SetPosition);
    AclientGameModeBase::GetCurrentClientGameMode().RegisterMainPlayer(this);
}
APlayerRole::~APlayerRole()
{
    AclientGameModeBase::GetCurrentClientGameMode().UnregisterMainPlayer(this);
}

