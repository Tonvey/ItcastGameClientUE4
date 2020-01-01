// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventDispatcher.h"

GameEventDispatcher::GameEventDispatcher()
{
}

GameEventDispatcher::~GameEventDispatcher()
{
}

void GameEventDispatcher::Init()
{
    auto &event = NetworkController::GetInstance().GetOnNewMessage();
    event.AddRaw(this,&GameEventDispatcher::OnNewGameMessage);
}
void GameEventDispatcher::OnNewGameMessage(GameSingleTLV::GameMsgType type,::google::protobuf::Message *msg)
{
    UE_LOG(LogTemp, Display, TEXT("GameEventDispatcher::OnNewGameMessage %d "), type );
}

void GameEventDispatcher::Register(GameMsgID_t id,SingleGameMsgDelegate &callback)
{
    int idx = int(id);
    if(idx>mGameMsgMap.Num())
    {
        mGameMsgMap.SetNum(idx,true);
    }
    mGameMsgMap[idx] = callback;
}
void GameEventDispatcher::Unregister(GameMsgID_t id)
{
}
