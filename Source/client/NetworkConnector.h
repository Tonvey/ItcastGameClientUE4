// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"

/**
 * 
 */
class CLIENT_API NetworkConnector
{
public:
	NetworkConnector();
	~NetworkConnector();
    bool Init();
private:
    FSocket *mSocket;
};
