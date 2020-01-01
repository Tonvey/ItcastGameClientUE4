// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkConnector.h"
#include <string>
#include "GameMsg.h"

/**
 * 
 */
class CLIENT_API NetProtocolResolver
{
public:
	NetProtocolResolver(TSharedPtr<NetworkConnector> &connector);
	~NetProtocolResolver();
    virtual TSharedPtr<GameMsg> ResolveMessage();
private:
    TSharedPtr<NetworkConnector> mConnector;
    std::string mLastBuf;
};
