// Fill out your copyright notice in the Description page of Project Settings.
#include "GameMsg.h"

FGameSingleTLV::FGameSingleTLV(FGameSingleTLV::ENUM_GameMsgID type, ::google::protobuf::Message *pbmsg)
    :m_MsgType(type), mPbMsg(pbmsg)
{
}
std::string FGameSingleTLV::serialize()
{
    std::string out;
    if (mPbMsg.IsValid())
    {
        out = mPbMsg->SerializeAsString();
    }
    return out;
}

FGameSingleTLV::FGameSingleTLV(ENUM_GameMsgID type, std::string content)
    :m_MsgType(type)
{

    //根据不同的消息id,然后反序列化为不同的protobuf对象
    switch (m_MsgType)
    {
    case GAME_MSG_LOGON_SYNCPID:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SyncPid);
            break;
        }
    case GAME_MSG_TALK_CONTENT:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::Talk);
            break;
        }
    case GAME_MSG_NEW_POSTION:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::Position);
            break;
        }
    case GAME_MSG_SKILL_TRIGGER:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SkillTrigger());
            break;
        }
    case GAME_MSG_SKILL_CONTACT:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SkillContact());
            break;
        }
    case GAME_MSG_CHANGE_WORLD:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::ChangeWorldRequest());
            break;
        }
    case GAME_MSG_BROADCAST:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::BroadCast);
            break;
        }
    case GAME_MSG_LOGOFF_SYNCPID:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SyncPid);
            break;
        }
    case GAME_MSG_SUR_PLAYER:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SyncPlayers);
            break;
        }
    case GAME_MSG_SKILL_BROAD:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SkillTrigger);
            break;
        }
    case GAME_MSG_SKILL_CONTACT_BROAD:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::SkillContact);
            break;
        }
    case GAME_MSG_CHANGE_WORLD_RESPONSE:
        {
            mPbMsg = TSharedPtr<::google::protobuf::Message>(new pb::ChangeWorldResponse);
            break;
        }
    default:
        break;
    }
    //反序列化
    if(mPbMsg.IsValid())
    {
        mPbMsg->ParseFromString(content);
    }
}
