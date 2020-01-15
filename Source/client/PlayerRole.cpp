// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"
#include "DataAdapter.h"

APlayerRole::APlayerRole()
{
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&APlayerRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&APlayerRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &APlayerRole::SetPosition);
}
APlayerRole::~APlayerRole()
{
}
void APlayerRole::SetPosition(int _pid,pb::Position _pos)
{
    if (_pid != mPid)
    {
        return;
    }
    auto location = DataAdapter::PostionSC(_pos);
    UE_LOG(LogTemp, Display, TEXT("PlayerRole::SetPosition x:%f y:%f z:%f"),location.X,location.Y,location.Z);
    this->SetActorLocation(location);
}
