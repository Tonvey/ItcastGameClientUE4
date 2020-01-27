// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkConnector.h"
#include "GameMsg.h"

/**
 * 
 */
class CLIENT_API NetProtocolResolver
{
public:
	NetProtocolResolver(TSharedPtr<NetworkConnector> &connector);
	~NetProtocolResolver();
    virtual GameMsgArray_t ResolveMessage();
    virtual void PushMsg(GameMsgArray_t &msg);
    virtual void PushMsg(FGameSingleTLV &msg);
    static void AppendMessageToString(FGameSingleTLV& singlePbMsg, std::string& dest);
private:
    TSharedPtr<NetworkConnector> mConnector;
    std::string mLastBuf;
};
