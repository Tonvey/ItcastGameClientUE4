// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include <string>

/**
 * 
 */
class CLIENT_API NetworkConnector
{
public:
	NetworkConnector(FString ip , uint16 port);
	~NetworkConnector();
    bool ReadData(std::string &data);
    void SendData(std::string &data);
    std::string Convert2Printable(std::string &_szData);
private:
    FSocket *mSocket;
    FString mIp;
    uint16 mPort;
};
