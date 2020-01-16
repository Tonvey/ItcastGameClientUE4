// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventDispatcher.h"
using namespace std;

GameEventDispatcher::GameEventDispatcher()
{
    UE_LOG(LogTemp, Display, TEXT("GameEventDispatcher::GameEventDispatcher"));
    NetworkController::GetInstance().GetOnNewMessage().AddRaw(this,&GameEventDispatcher::OnNewGameMessage);
}

GameEventDispatcher::~GameEventDispatcher()
{
    UE_LOG(LogTemp, Display, TEXT("GameEventDispatcher::~GameEventDispatcher"));
}

void GameEventDispatcher::Init()
{
}
void GameEventDispatcher::OnNewGameMessage(GameMsgID_t type,GameMsg_t *_msg)
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
                //talk
                break;
            }
            case 2:
            {
                //new player
                mOnNewPlayer.Broadcast(msg->pid(), msg->username());
                //TODO: 这样分离可能会导致其他玩家角色不能及时处理移动消息的问题
                mOnSyncPosition.Broadcast(msg->pid(), msg->p());
                break;
            }
            case 4:
            {
                //move
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

//void GameEventDispatcher::Register(GameMsgID_t id,SingleGameMsgDelegate &callback)
//{
//    int idx = int(id);
//    if(idx>mGameMsgMap.Num())
//    {
//        mGameMsgMap.SetNum(idx,true);
//    }
//    mGameMsgMap[idx].Add(callback);
//}
//void GameEventDispatcher::Unregister(GameMsgID_t id)
//{
//}
