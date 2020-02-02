// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//TODO COreMinimal 不包括list
#include "CoreMinimal.h"
//#include "Core.h"
#include "proto/msg.pb.h"
#include <list>
#include "GameMsg.generated.h"

typedef ::google::protobuf::Message GameMsg_t;

USTRUCT(BlueprintType)
struct CLIENT_API FGameMsgPack
{
	GENERATED_BODY()
	TSharedPtr<GameMsg_t> msg;
	FGameMsgPack()=default;
	FGameMsgPack(GameMsg_t* Msg):msg(Msg) {}
};
UENUM(BlueprintType)
enum EGameMsgID {
	GAME_MSG_LOGON_SYNCPID = 1,
	GAME_MSG_TALK_CONTENT = 2,
	GAME_MSG_NEW_POSTION = 3,
	GAME_MSG_SKILL_TRIGGER = 4,
	GAME_MSG_SKILL_CONTACT = 5,
	GAME_MSG_CHANGE_WORLD = 6,

	GAME_MSG_BROADCAST = 200,
	GAME_MSG_LOGOFF_SYNCPID = 201,
	GAME_MSG_SUR_PLAYER = 202,
	GAME_MSG_SKILL_BROAD = 204,
	GAME_MSG_SKILL_CONTACT_BROAD = 205,
	GAME_MSG_CHANGE_WORLD_RESPONSE = 206,
};
USTRUCT(BlueprintType)
struct CLIENT_API FGameSingleTLV
{
	GENERATED_BODY()
    //定义逻辑消息的类型
    std::string serialize();
    FGameSingleTLV() = default;
    FGameSingleTLV(const FGameSingleTLV &) = default;
    FGameSingleTLV(EGameMsgID type, std::string content);
    FGameSingleTLV(EGameMsgID type, ::google::protobuf::Message* pbmsg);
    EGameMsgID m_MsgType;
    //定义一个父类对象的指针,用来存储不同类型的子类
    TSharedPtr<::google::protobuf::Message> mPbMsg;
};
typedef EGameMsgID GameMsgID_t;
typedef std::list<FGameSingleTLV> GameMsgArray_t;

