// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkController.h"

NetworkController::NetworkController()
    :isPaused(false)
{
}

NetworkController::~NetworkController()
{
    Finish();
}
void NetworkController::Init(FString ip , uint16 port)
{
    mConnector= decltype(mConnector)( new NetworkConnector(ip,port));
    mProtocol= decltype(mProtocol)( new NetProtocolResolver(mConnector));
}
void NetworkController::Finish()
{
    mConnector =decltype(mConnector)();
    mProtocol= decltype(mProtocol)();
    isPaused = false;
}
void NetworkController::Reset()
{
    Finish();
}
void NetworkController::ProcessNetworkMessage()
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

void NetworkController::PushMsg(GameMsgArray_t &msg)
{
    mProtocol->PushMsg(msg);
}

void NetworkController::PushMsg(GameSingleTLV& msg)
{
    mProtocol->PushMsg(msg);
}

void NetworkController::PauseProcessMessage()
{
    isPaused = true;
}

void NetworkController::ResumeProcessMessage()
{
    isPaused = false;
}

