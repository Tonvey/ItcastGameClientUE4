// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkConnector.h"
#include "NetProtocolResolver.h"

/**
 * 
 */
class CLIENT_API NetworkController
{
public:
    static NetworkController &GetInstance(){return smInstance;}
	NetworkController();
	virtual ~NetworkController();
    virtual void Init(FString ip , uint16 port);
    virtual void Finish();
    virtual void Reset();
    virtual void ProcessNetworkMessage();
    
private:
    static NetworkController smInstance;
    TSharedPtr<NetworkConnector> mConnector;
    TSharedPtr<NetProtocolResolver> mProtocol;
};
