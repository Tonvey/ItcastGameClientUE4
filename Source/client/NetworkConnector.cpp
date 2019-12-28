// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkConnector.h"
#include "SocketSubsystem.h"
#include "AddressInfoTypes.h"
#include "Interfaces/IPv4/IPv4Address.h"

NetworkConnector::NetworkConnector()
:mSocket(nullptr)
{
}

bool NetworkConnector::Init()
{
    if(mSocket!=nullptr)
    {
        delete mSocket;
    }
    mSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    FString addrStr = FString(TEXT("127.0.0.1"));
    FIPv4Address ip;
    FIPv4Address::Parse(addrStr, ip);
    auto addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr(ip.Value, 8899);
    mSocket->Connect(*addr);
    
    FString serialized = TEXT("loadPlayer|1");
    TCHAR *serializedChar = serialized.GetCharArray().GetData();
    int32 size = FCString::Strlen(serializedChar);
    int32 sent = 0;
    return true;
}
NetworkConnector::~NetworkConnector()
{
    if(mSocket!=nullptr)
    {
        delete mSocket;
        mSocket=nullptr;
    }
}
