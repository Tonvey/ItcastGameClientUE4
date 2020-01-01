// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkController.h"
#include "GameMsg.h"
#include "Singleton.hpp"

/**
 *
 */
class CLIENT_API GameEventDispatcher : public Singleton<GameEventDispatcher>
{
public:
    typedef ::google::protobuf::Message GameMsg_t;
    DECLARE_DELEGATE_OneParam(SingleGameMsgDelegate,GameMsg_t);
    typedef TArray<SingleGameMsgDelegate> GameMsgMap_t;
    typedef GameSingleTLV::GameMsgType GameMsgID_t;
	GameEventDispatcher();
	~GameEventDispatcher();
    void OnNewGameMessage(GameSingleTLV::GameMsgType,GameMsg_t*);
    void Register(GameMsgID_t id,SingleGameMsgDelegate &callback);
    void Unregister(GameMsgID_t id);
    void Init();
private:
    GameMsgMap_t mGameMsgMap;
};
