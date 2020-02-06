// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRole.h"
#include "GameEventDispatcher.h"
#include "GameFramework/Controller.h"
#include "DataAdapter.h"
#include "NetworkMessageFactoryUtil.h"

APlayerRole::APlayerRole()
    :mLastPositionSyncInterval(0.0f)
{
}
void APlayerRole::Init()
{
    //TODO 想要让C++和bp都有事件可以响应，目前只能是引用dynamic multicast delegate，因为dynamic通过字符串反射
    //获取C++或者BP的函数，所以性能上低于普通delegate,BP那边要bind一个event上来
    //delegate 要以UPROPERTY( BlueprintAssignable)的方式存在
    //FScriptDelegate d;
    //d.BindUFunction(this, "SetPid");
    //UGameEventDispatcher::GetInstance().GetOnSyncPid().Add(d);
    Super::Init();
    UGameEventDispatcher::GetInstance().GetOnSyncPid().AddUObject(this,&APlayerRole::SetPid);
    UGameEventDispatcher::GetInstance().GetOnSyncPlayerName().AddUObject(this,&APlayerRole::SetPlayerName);
    UGameEventDispatcher::GetInstance().GetOnSyncPosition().AddUObject(this, &APlayerRole::SetPlayerGroundLocation);
}

APlayerRole::~APlayerRole()
{
}

void APlayerRole::SetPid(int _pid)
{
    Super::SetPid(_pid);
    UGameEventDispatcher::GetInstance().GetOnMainPlayerSync().Broadcast(this, _pid);
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
           auto pbPos = this->GetPositionPack();
           auto msg = UNetworkMessageFactoryUtil::MakeSyncPosition(pbPos);
		   UNetworkController::GetInstance()->PushMsg(msg);
		   mLastPositionSyncInterval = 0.0f;
           mLastSyncPosition = newPos;
       }
   }
}

