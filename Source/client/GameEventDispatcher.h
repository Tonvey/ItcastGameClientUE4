// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkController.h"
#include "GameMsg.h"
#include "Singleton.hpp"

#define DECLARE_EVENT_MEMBER_INSTANCE(ev_name) \
public:\
    UFUNCTION(BlueprintCallable)\
    ev_name Get##ev_name()const\
    {\
        return m##ev_name;                       \
    }\
protected:\
    UPROPERTY(BlueprintAssignable, Category = "Event")\
    ev_name m##ev_name;
/**
 *
 */
class CLIENT_API GameEventDispatcher : public Singleton<GameEventDispatcher>
{
public:
    DECLARE_EVENT_OneParam(GameEventDispatcher, OnSyncPid,int);
    DECLARE_EVENT_OneParam(GameEventDispatcher, OnSyncPlayerName,std::string);
    DECLARE_EVENT_OneParam(GameEventDispatcher, OnSyncPosition,FVector);

    DECLARE_EVENT_MEMBER_INSTANCE(OnSyncPid);
    DECLARE_EVENT_MEMBER_INSTANCE(OnSyncPlayerName);
    DECLARE_EVENT_MEMBER_INSTANCE(OnSyncPosition);
public:
    typedef ::google::protobuf::Message GameMsg_t;
    DECLARE_DELEGATE_OneParam(SingleGameMsgDelegate,GameMsg_t*);
    typedef TArray<TArray<SingleGameMsgDelegate>> GameMsgMap_t;
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
