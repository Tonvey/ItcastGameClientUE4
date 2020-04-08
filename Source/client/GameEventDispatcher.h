// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkController.h"
#include "GameMsg.h"
#include "GameEventDispatcher.generated.h"

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
#define DECLARE_MY_EVENT_MEMBER_FourParams(owner_type,ev_name,t1,t2,t3,t4) \
public:\
    DECLARE_EVENT_FourParams(owner_type,ev_name,t1,t2,t3,t4)\
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)
#define DECLARE_MY_EVENT_MEMBER_FiveParams(owner_type,ev_name,t1,t2,t3,t4,t5) \
public:\
    DECLARE_EVENT_FiveParams(owner_type,ev_name,t1,t2,t3,t4,t5)\
    DECLARE_EVENT_MEMBER_INSTANCE(ev_name)

/**
 *
 */
UCLASS(BlueprintType)
class CLIENT_API UGameEventDispatcher : public UObject
{
	GENERATED_BODY()
public:
    static UGameEventDispatcher *GetInstance();
    DECLARE_MY_EVENT_MEMBER_OneParam(UGameEventDispatcher,OnSyncPid,int);
    DECLARE_MY_EVENT_MEMBER_OneParam(UGameEventDispatcher,OnSyncPlayerName,std::string);
    DECLARE_MY_EVENT_MEMBER_OneParam(UGameEventDispatcher,OnPlayerLogoff,int);
    DECLARE_MY_EVENT_MEMBER_TwoParams(UGameEventDispatcher,OnSyncPosition,int,pb::Position);
    DECLARE_MY_EVENT_MEMBER_TwoParams(UGameEventDispatcher,OnMainPlayerSync,APlayerRole *,int);
    // new player : pid , name , position
    DECLARE_MY_EVENT_MEMBER_ThreeParams(UGameEventDispatcher,OnNewPlayer,int,std::string,pb::Position);
    //chat : pid,name,content
    DECLARE_MY_EVENT_MEMBER_ThreeParams(UGameEventDispatcher, OnSyncChat,int,std::string,std::string);

    //srcid , target world id , res
    DECLARE_MY_EVENT_MEMBER_ThreeParams(UGameEventDispatcher, OnChangeWorld,int,int,int);
    //src_pid , skill_id , bulletId , playe_trigger_pos , velocity
    DECLARE_MY_EVENT_MEMBER_FiveParams(UGameEventDispatcher, OnSkillTrigger,int,int,int,const pb::Position&,const pb::Velocity&);
    //src_pid , target_pid ,skillId, bulletId , contact_pos
    DECLARE_MY_EVENT_MEMBER_FiveParams(UGameEventDispatcher, OnSkillContact,int,int,int,int,const pb::Position&);
public:
    //DECLARE_DELEGATE_OneParam(SingleGameMsgDelegate,GameMsg_t*);
    //typedef TArray<TArray<SingleGameMsgDelegate>> GameMsgMap_t;
    //void Register(GameMsgID_t id,SingleGameMsgDelegate &callback);
    //void Unregister(GameMsgID_t id);
    void Init();
    void OnNewGameMessage(GameMsgID_t,GameMsg_t*);
    virtual void Reset();

private:
	UGameEventDispatcher();
	~UGameEventDispatcher();
    //GameMsgMap_t mGameMsgMap;
    FDelegateHandle handle;
};
