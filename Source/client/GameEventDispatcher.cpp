// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventDispatcher.h"
using namespace std;

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
void GameEventDispatcher::OnNewGameMessage(GameSingleTLV::ENUM_GameMsgID type,::google::protobuf::Message *_msg)
{
    UE_LOG(LogTemp, Display, TEXT("GameEventDispatcher::OnNewGameMessage %d "), type );
    switch(type)
    {
    case GameMsgID_t::GAME_MSG_LOGON_SYNCPID:
        {
            auto msg = static_cast<pb::SyncPid*>(_msg);
            int pid = msg->pid();
            string userName = msg->username();
            mOnSyncPid.Broadcast(pid);
            mOnSyncPlayerName.Broadcast(userName);
            UE_LOG(LogTemp, Display, TEXT("on pid %d  , on name : %s"), pid,UTF8_TO_TCHAR(userName.c_str()));
            break;
        }
    case GameMsgID_t::GAME_MSG_BROADCAST:
        {
            auto msg = static_cast<pb::BroadCast*>(_msg);
            switch (msg->tp())
            {
            case 1:
            {
                //聊天
                break;
            }
            case 2:
            {
                //新玩家初始位置
                mOnNewPlayer.Broadcast(msg->pid(), msg->username());
                mOnSyncPosition.Broadcast(msg->pid(), msg->p());
                break;
            }
            case 4:
            {
                //玩家移动同步
                mOnSyncPosition.Broadcast(msg->pid(), msg->p());
                break;
            }
            default:
                break;
            }
            break;
        }
    case GameMsgID_t::GAME_MSG_LOGOFF_SYNCPID:
        {
            auto msg = static_cast<pb::SyncPid*>(_msg);
            int pid = msg->pid();
            mOnPlayerLogoff.Broadcast(pid);
            break;
        }
    case GameMsgID_t::GAME_MSG_SUR_PLAYER:
        {
            break;
        }
    case GameMsgID_t::GAME_MSG_SKILL_BROAD:
        {
            break;
        }
    case GameMsgID_t::GAME_MSG_SKILL_CONTACT_BROAD:
        {
            break;
        }
    case GameMsgID_t::GAME_MSG_CHANGE_WORLD_RESPONSE:
        {
            break;
        }
    default:
        {
            break;
        }
    }
}

void GameEventDispatcher::Register(GameMsgID_t id,SingleGameMsgDelegate &callback)
{
    int idx = int(id);
    if(idx>mGameMsgMap.Num())
    {
        mGameMsgMap.SetNum(idx,true);
    }
    mGameMsgMap[idx].Add(callback);
}
void GameEventDispatcher::Unregister(GameMsgID_t id)
{
}
