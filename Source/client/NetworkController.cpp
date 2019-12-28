// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkController.h"

NetworkController NetworkController::smInstance;

NetworkController::NetworkController()
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
}
void NetworkController::Reset()
{
    Finish();
}
    
void NetworkController::ProcessNetworkMessage()
{
    mProtocol->ResolveMessage();
}
