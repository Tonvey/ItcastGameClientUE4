// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkController.h"
#include "GameMsg.h"
#include "Singleton.hpp"

class APlayerRole;
#define DECLARE_EVENT_MEMBER_INSTANCE(ev_name) \
public:\
    UFUNCTION(BlueprintCallable)\
    ev_name &Get##ev_name()\
    {\
        return m##ev_name;                       \
    }\
protected:\
    UPROPERTY(BlueprintReadOnly, Category = "Event")\
    ev_name m##ev_name;\


#define DECLARE_MY_EVENT_MEMBER(owner_type,ev_name) \
public:\
    DECLARE_EVENT(owner_type,ev_name)\
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)

#define DECLARE_MY_EVENT_MEMBER_OneParam(owner_type,ev_name,...) \
public:\
    DECLARE_EVENT_OneParam(owner_type,ev_name,__VA_ARGS__) \
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)

#define DECLARE_MY_EVENT_MEMBER_TwoParams(owner_type,ev_name,t1,t2) \
public:\
    DECLARE_EVENT_TwoParams(owner_type,ev_name,t1,t2)\
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)

#define DECLARE_MY_EVENT_MEMBER_ThreeParams(owner_type,ev_name,t1,t2,t3) \
public:\
    DECLARE_EVENT_ThreeParams(owner_type,ev_name,t1,t2,t3)\
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)

/**
 *
 */
class CLIENT_API GameEventDispatcher : public Singleton<GameEventDispatcher>
{
public:
    friend Singleton<GameEventDispatcher>;
    DECLARE_MY_EVENT_MEMBER_OneParam(GameEventDispatcher,OnSyncPid,int);
    DECLARE_MY_EVENT_MEMBER_OneParam(GameEventDispatcher,OnSyncPlayerName,std::string);
    DECLARE_MY_EVENT_MEMBER_OneParam(GameEventDispatcher,OnPlayerLogoff,int);
    DECLARE_MY_EVENT_MEMBER_TwoParams(GameEventDispatcher,OnSyncPosition,int,pb::Position);
    DECLARE_MY_EVENT_MEMBER_TwoParams(GameEventDispatcher,OnMainPlayerSync,APlayerRole *,int);
    // new player : pid , name , position
    DECLARE_MY_EVENT_MEMBER_ThreeParams(GameEventDispatcher,OnNewPlayer,int,std::string,pb::Position);
    //chat : pid,name,content
    DECLARE_MY_EVENT_MEMBER_ThreeParams(GameEventDispatcher, OnSyncChat,int,std::string,std::string);
public:
    //DECLARE_DELEGATE_OneParam(SingleGameMsgDelegate,GameMsg_t*);
    //typedef TArray<TArray<SingleGameMsgDelegate>> GameMsgMap_t;
    //void Register(GameMsgID_t id,SingleGameMsgDelegate &callback);
    //void Unregister(GameMsgID_t id);
    void Init();
    void OnNewGameMessage(GameMsgID_t,GameMsg_t*);

private:
	GameEventDispatcher();
	~GameEventDispatcher();
    //GameMsgMap_t mGameMsgMap;
};
