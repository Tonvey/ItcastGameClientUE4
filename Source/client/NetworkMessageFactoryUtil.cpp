// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMessageFactoryUtil.h"

GameSingleTLV UNetworkMessageFactoryUtil::MakeTalkContent(const FText &_content)
{
    auto pbMsg = new pb::Talk;
    pbMsg->set_content(TCHAR_TO_UTF8(*_content.ToString()));
    GameSingleTLV singleMsg(GameMsgID_t::GAME_MSG_TALK_CONTENT,
        pbMsg);
    return singleMsg;
}
GameSingleTLV UNetworkMessageFactoryUtil::MakeSyncPosition(pb::Position &_posistion)
{
    GameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_NEW_POSTION,
        new pb::Position(_posistion));
    return singleMsg;
}
GameSingleTLV UNetworkMessageFactoryUtil::MakeChangeWorldRequest(int _pid, int _src,int _target)
{
    auto pbMsg = new pb::ChangeWorldRequest;
    pbMsg->set_pid(_pid);
    pbMsg->set_srcid(_src);
    pbMsg->set_targetid(_target);
    GameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_CHANGE_WORLD,
        pbMsg);
    return singleMsg;
}

