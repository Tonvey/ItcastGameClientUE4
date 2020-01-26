// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMessageFactoryUtil.h"

TSharedPtr<GameMsg> UNetworkMessageFactoryUtil::MakeTalkContent(const FText &_content)
{
    TSharedPtr<GameMsg> ret(new GameMsg);
    auto pbMsg = new pb::Talk;
    pbMsg->set_content(TCHAR_TO_UTF8(*_content.ToString()));
    TSharedPtr<GameSingleTLV> singleMsg(new GameSingleTLV(
        GameMsgID_t::GAME_MSG_TALK_CONTENT,
        pbMsg));
    ret->mMsgList.push_back(singleMsg);
    return ret;
}
