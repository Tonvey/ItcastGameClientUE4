// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//COreMinimal 不包括list
#include "CoreMinimal.h"
//#include "Core.h"
#include "proto/msg.pb.h"
#include <list>
#include "GameMsg.generated.h"

typedef ::google::protobuf::Message GameMsg_t;

USTRUCT(BlueprintType)
struct FGameMsgPack
{
	GENERATED_BODY()
    ~FGameMsgPack()
    {
        if (msg != nullptr)
        {
            delete msg;
        }
    }
    GameMsg_t *msg;
};

USTRUCT(BlueprintType)
struct FGameSingleTLV//: public UObject
{
	GENERATED_BODY()
    //定义逻辑消息的类型
    enum ENUM_GameMsgID {
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
    std::string serialize();
    FGameSingleTLV() = default;
    FGameSingleTLV(const FGameSingleTLV &) = default;
    FGameSingleTLV(ENUM_GameMsgID type, std::string content);
    FGameSingleTLV(ENUM_GameMsgID type, ::google::protobuf::Message* pbmsg);
    ENUM_GameMsgID m_MsgType;
    //定义一个父类对象的指针,用来存储不同类型的子类
    TSharedPtr<::google::protobuf::Message> mPbMsg;
};
typedef FGameSingleTLV::ENUM_GameMsgID GameMsgID_t;
typedef std::list<FGameSingleTLV> GameMsgArray_t;

