// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"

APlayerRole::APlayerRole()
{
    GameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&APlayerRole::SetPid);
    GameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&APlayerRole::SetPlayerName);
    GameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &APlayerRole::SetPosition);
}
APlayerRole::~APlayerRole()
{
}
void APlayerRole::SetPid(int _pid)
{
    this->mPid = _pid;
    this->mOnSetPid.Broadcast(_pid);
}
void APlayerRole::SetPlayerName(std::string _playerName)
{
    mPlayerName = UTF8_TO_TCHAR(_playerName.c_str());
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    if (this->mPlayerNameTextComp != nullptr)
    {
		this->mPlayerNameTextComp->SetText(mPlayerName);
    }
}
void APlayerRole::SetPosition(int _pid,pb::Position _pos)
{
    if (_pid != mPid)
    {
        return;
    }
    AController *ctl = this->Controller;
    FVector location;
    location.X = _pos.z();
    location.Y= _pos.x();
    location.Z = _pos.y();
    location *= 100;
    UE_LOG(LogTemp, Display, TEXT("PlayerRole::SetPosition x:%f y:%f z:%f"),location.X,location.Y,location.Z);
    this->SetActorLocation(location);
    //SetLocation(location);
}
void APlayerRole::SetPlayerName(FString _playerName)
{
    mPlayerName = _playerName;
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    if (this->mPlayerNameTextComp != nullptr)
    {
		this->mPlayerNameTextComp->SetText(mPlayerName);
    }
}
