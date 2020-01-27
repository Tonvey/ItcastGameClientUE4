// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkController.h"
#include "GameSingletonManager.h"

UNetworkController& UNetworkController::GetInstance()
{
    auto ret = UGameSingletonManager::GetInstance()->GetNetworkController();
    return *ret;
}

UNetworkController::UNetworkController()
    :isPaused(false)
{
}

UNetworkController::~UNetworkController()
{
    Finish();
}
void UNetworkController::Init(FString ip , uint16 port)
{
    mConnector= decltype(mConnector)( new NetworkConnector(ip,port));
    mProtocol= decltype(mProtocol)( new NetProtocolResolver(mConnector));
}
void UNetworkController::Finish()
{
    mConnector =decltype(mConnector)();
    mProtocol= decltype(mProtocol)();
    isPaused = false;
}
void UNetworkController::Reset()
{
    Finish();
}
void UNetworkController::ProcessNetworkMessage()
{
    if (mLastMessages.size()==0)
    {
		mLastMessages = mProtocol->ResolveMessage();
    }
    if (mLastMessages.size()==0)
    {
        return;
    }
    while (mLastMessages.size()>0)
    {
        if (isPaused)
        {
            break;
        }
        auto tlv = mLastMessages.front();
        mLastMessages.pop_front();
		OnNewGameMessage.Broadcast(tlv.m_MsgType, tlv.mPbMsg.Get());
    }
}

void UNetworkController::PushMsg(GameMsgArray_t &msg)
{
    mProtocol->PushMsg(msg);
}

void UNetworkController::PushMsg(FGameSingleTLV& msg)
{
    mProtocol->PushMsg(msg);
}

void UNetworkController::PauseProcessMessage()
{
    isPaused = true;
}

void UNetworkController::ResumeProcessMessage()
{
    isPaused = false;
}

