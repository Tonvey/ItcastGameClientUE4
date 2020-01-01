// Fill out your copyright notice in the Description page of Project Settings.


#include "NetProtocolResolver.h"
#include <string>
#include "GameMsg.h"
using std::string;

NetProtocolResolver::NetProtocolResolver(TSharedPtr<NetworkConnector> &connector)
{
    mConnector = connector;
}

NetProtocolResolver::~NetProtocolResolver()
{
}

TSharedPtr<GameMsg> NetProtocolResolver::ResolveMessage()
{
    string _szInput;
    if(!mConnector->ReadData(_szInput)||_szInput.size()==0)
    {
        return nullptr;
    }
    mLastBuf.append(_szInput);
    GameMsg *gameMsg = nullptr;
    //数据长度至少要大于8才做处理
    while (mLastBuf.size() >= 8)
    {
        // 0x01 0x02 0x03 0x04    ->   0x04030201
        uint32 len =
            (uint8)mLastBuf[0] |
            (uint8)mLastBuf[1] << 8 |
            (uint8)mLastBuf[2] << 16 |
            (uint8)mLastBuf[3] << 24;
        uint32 msgType =
            (uint8)mLastBuf[4] |
            (uint8)mLastBuf[5] << 8 |
            (uint8)mLastBuf[6] << 16 |
            (uint8)mLastBuf[7] << 24;
        //cout << "len:" << len << " msgType:" << msgType << endl;
        UE_LOG(LogTemp, Display, TEXT("process message , len %u , type : %u\n"),len,msgType);
        //判断消息内容长度够不够  01000000010000000102000000020000000202
        if (mLastBuf.size() - 8 >= len)
        {
            //从字符串取子串就可以   该子串是protobuf的一个消息
            string msgContent = mLastBuf.substr(8, len);
            //buf要清理掉这个报文
            mLastBuf.erase(0, 8 + len);
            //产生一个SingletTLV
            auto msg = new GameSingleTLV((GameSingleTLV::GameMsgType)msgType, msgContent);
            if(msg->mPbMsg==nullptr)
            {
                continue;
            }

            if (gameMsg == nullptr)
            {
                gameMsg = new GameMsg;
            }
            //将singletlv加到GameMsg
            gameMsg->mMsgList.push_back(msg);
        }
        else
        {
            //剩下长度不够,就不要继续循环等待下一次数据到来再出来
            break;
        }
    }
    //返回值包含多个逻辑消息的列表
    return TSharedPtr<GameMsg>(gameMsg);
}
