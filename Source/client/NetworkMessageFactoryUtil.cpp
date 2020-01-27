// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMessageFactoryUtil.h"

UNetworkController *UNetworkMessageFactoryUtil::GetNetworkControllerInstance()
{
    return &UNetworkController::GetInstance();
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeTalkContent(const FText &_content)
{
    auto pbMsg = new pb::Talk;
    pbMsg->set_content(TCHAR_TO_UTF8(*_content.ToString()));
    FGameSingleTLV singleMsg = { GameMsgID_t::GAME_MSG_TALK_CONTENT,
        pbMsg };
    return singleMsg;
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeSyncPosition(const FGameMsgPack &_pb_position)
{
    auto &_position = static_cast<pb::Position&>(*_pb_position.msg);
    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_NEW_POSTION,
        new pb::Position(_position));
    return singleMsg;
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeChangeWorldRequest(int _pid, int _src,int _target)
{
    auto pbMsg = new pb::ChangeWorldRequest;
    pbMsg->set_pid(_pid);
    pbMsg->set_srcid(_src);
    pbMsg->set_targetid(_target);
    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_CHANGE_WORLD,
        pbMsg);
    return singleMsg;
}

