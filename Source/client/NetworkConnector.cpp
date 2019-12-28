// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkConnector.h"
#include "SocketSubsystem.h"
#include "AddressInfoTypes.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include <cstdlib>
using std::string;

NetworkConnector::NetworkConnector(FString ip , uint16 port)
:mSocket(nullptr),
mIp(ip),
mPort(port)
{
    mSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    FIPv4Address aip;
    FIPv4Address::Parse(mIp, aip);
    auto addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr(aip.Value, mPort);
    mSocket->Connect(*addr);
    mSocket->SetNonBlocking(true);
    int32 newSize ;
    mSocket->SetReceiveBufferSize(1024*8,newSize);
}

NetworkConnector::~NetworkConnector()
{
    if(mSocket!=nullptr)
    {
        delete mSocket;
        mSocket=nullptr;
    }
}
std::string NetworkConnector::Convert2Printable(std::string &_szData)
{
    char *pcTemp = (char *)calloc(1UL, _szData.size() * 3 + 1);
    int iCurPos = 0;

    if (NULL != pcTemp)
    {
        for (int i = 0; i < _szData.size(); ++i)
        {
            iCurPos += sprintf(pcTemp + iCurPos, "%02X ", (unsigned char)_szData[i]);
        }
        pcTemp[iCurPos] = 0;
    }

    std::string szRet = std::string(pcTemp);
    free(pcTemp);

    return szRet;
}
bool NetworkConnector::ReadData(string &data)
{
    uint8 buf[1024*8];
    int32 readSum = 0;
    int32 readSize = 0;
    memset(buf,0,sizeof(buf));
    bool readResult = true;
    while((readResult=mSocket->Recv(buf,sizeof(buf),readSize)))
    {
        readSum+=readSize;
        if(readSize==0)
        {
            //UE_LOG(LogTemp, Display, TEXT("NetworkConnector::ReadEndChunk") );
            break;
        }
        data.append((char*)buf,readSize);
    }
    if(!readResult)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkConnector::ReadData error") );
    }
    if(readSum!=0)
    {
        UE_LOG(LogTemp, Display, TEXT("recv : %s\n"),ANSI_TO_TCHAR(Convert2Printable(data).c_str()));
    }
    return readResult;
}

void NetworkConnector::SendData(string &data)
{
    uint8 *buf = new uint8[data.size()];
    int32 byteSend;
    if(!mSocket->Send(buf,data.size(),byteSend))
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkConnector::ReadData error1") );
    }
    if(byteSend!=data.size())
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkConnector::ReadData error2") );
    }
    UE_LOG(LogTemp, Display, TEXT("send : %s\n"),Convert2Printable(data).c_str());
    delete[] buf;
}
