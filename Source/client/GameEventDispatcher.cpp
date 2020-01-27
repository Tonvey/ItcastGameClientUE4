// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventDispatcher.h"
#include "GameSingletonManager.h"
using namespace std;

UGameEventDispatcher &UGameEventDispatcher::GetInstance()
{
    auto ret = UGameSingletonManager::GetInstance()->GetGameEventDispatcher();
    return *ret;
}
UGameEventDispatcher::UGameEventDispatcher()
{
    UE_LOG(LogTemp, Display, TEXT("UGameEventDispatcher::UGameEventDispatcher"));
}

UGameEventDispatcher::~UGameEventDispatcher()
{
    UE_LOG(LogTemp, Display, TEXT("UGameEventDispatcher::~UGameEventDispatcher"));
}

void UGameEventDispatcher::Init()
{
    UNetworkController::GetInstance().GetOnNewMessage().AddUObject(this,&UGameEventDispatcher::OnNewGameMessage);
}
void UGameEventDispatcher::OnNewGameMessage(GameMsgID_t type,GameMsg_t *_msg)
{
    UE_LOG(LogTemp, Display, TEXT("UGameEventDispatcher::OnNewGameMessage %d "), type );
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
                mOnNewPlayer.Broadcast(msg->pid(), msg->username(),msg->p());
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
            auto msg = static_cast<pb::SyncPlayers*>(_msg);
            auto players = msg->ps();
            for (auto& p : players)
            {
                mOnNewPlayer.Broadcast(p.pid(), p.username(),p.p());
            }
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
            auto msg = static_cast<pb::ChangeWorldResponse*>(_msg);
            int srcid = msg->srcid();
            int targetid = msg->targetid();
            int res = msg->changeres();
            mOnChangeWorld.Broadcast(srcid, targetid, res);
            break;
        }
    default:
        {
            break;
        }
    }
}

void UGameEventDispatcher::Reset()
{
    mOnSyncPid.Clear();
	mOnSyncPlayerName.Clear();
    mOnPlayerLogoff.Clear();
    mOnSyncPosition.Clear();
    mOnMainPlayerSync.Clear();
    mOnNewPlayer.Clear();
    mOnSyncChat.Clear();
}

//void UGameEventDispatcher::Register(GameMsgID_t id,SingleGameMsgDelegate &callback)
//{
//    int idx = int(id);
//    if(idx>mGameMsgMap.Num())
//    {
//        mGameMsgMap.SetNum(idx,true);
//    }
//    mGameMsgMap[idx].Add(callback);
//}
//void UGameEventDispatcher::Unregister(GameMsgID_t id)
//{
//}
