// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkConnector.h"
#include "NetProtocolResolver.h"
#include "Singleton.hpp"

/**
 *
 */
class CLIENT_API NetworkController : public Singleton<NetworkController>
{
public:
	NetworkController();
	virtual ~NetworkController();
    virtual void Init(FString ip , uint16 port);
    virtual void Finish();
    virtual void Reset();
    virtual void ProcessNetworkMessage();
    virtual void PushMsg(TSharedPtr<GameMsg> &msg);
    DECLARE_EVENT_TwoParams(NetworkController, NewGameMessage,GameSingleTLV::ENUM_GameMsgID,::google::protobuf::Message*);
    virtual NewGameMessage &GetOnNewMessage(){return OnNewGameMessage;};
    virtual void PauseProcessMessage();
    virtual void ResumeProcessMessage();
private:
    TSharedPtr<NetworkConnector> mConnector;
    TSharedPtr<NetProtocolResolver> mProtocol;
    NewGameMessage OnNewGameMessage;
    bool isPaused;
    TSharedPtr<GameMsg> mLastMessages;
};
