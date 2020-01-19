// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"
#include "DataAdapter.h"

APlayerRole::APlayerRole()
    :mLastPositionSyncInterval(0.0f)
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

void APlayerRole::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   mLastPositionSyncInterval += DeltaTime;
   if (mLastPositionSyncInterval>0.1f)
   {
       auto newPb = this->GetPosition();
       FVector4 newPos;
       newPos.X = newPb.x();
       newPos.Y = newPb.y();
       newPos.Z = newPb.z();
       newPos.W = newPb.v();
       if (newPos != mLastSyncPosition)
       {
		   auto msg = MakeSyncPosition();
		   NetworkController::GetInstance().PushMsg(msg);
		   mLastPositionSyncInterval = 0.0f;
           mLastSyncPosition = newPos;
       }
   }
}

TSharedPtr<GameMsg> APlayerRole::MakeSyncPosition() const
{
    TSharedPtr<GameMsg> ret(new GameMsg);
    auto singleMsg = new GameSingleTLV(
        GameMsgID_t::GAME_MSG_NEW_POSTION,
        new pb::Position(this->GetPosition()));
    ret->mMsgList.push_back(singleMsg);
    return ret;
}

