// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkMessageFactoryUtil.h"
#include "DataAdapter.h"

FGameMsgPack UNetworkMessageFactoryUtil::MakeVelocityPack(const FVector& vec)
{
    auto v = new pb::Velocity;
    auto p = DataAdapter::PostionCS(vec);
    v->set_x(p.x());
    v->set_y(p.y());
    v->set_z(p.z());
    return { v };
}
FGameMsgPack UNetworkMessageFactoryUtil::MakePositionPack(int hp, const FVector& vec)
{
    auto p = DataAdapter::PostionCS(vec);
    p.set_bloodvalue(hp);
    return { new pb::Position(p) };
}

UNetworkController *UNetworkMessageFactoryUtil::GetNetworkControllerInstance()
{
    return UNetworkController::GetInstance();
}
UGameEventDispatcher* UNetworkMessageFactoryUtil::GetGameEventDispatcher()
{
    return &UGameEventDispatcher::GetInstance();
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeTalkContent(const FText &_content)
{
    auto pbMsg = new pb::Talk;
    pbMsg->set_content(TCHAR_TO_UTF8(*_content.ToString()));
    FGameSingleTLV singleMsg = { GameMsgID_t::GAME_MSG_TALK_CONTENT,
        pbMsg };
    return singleMsg;
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeSyncPosition(const FGameMsgPack &_pb_position)
{
    auto &_position = static_cast<pb::Position&>(*_pb_position.msg);
    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_NEW_POSTION,
        new pb::Position(_position));
    return singleMsg;
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeChangeWorldRequest(int _pid, int _src,int _target)
{
    auto pbMsg = new pb::ChangeWorldRequest;
    pbMsg->set_pid(_pid);
    pbMsg->set_srcid(_src);
    pbMsg->set_targetid(_target);
    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_CHANGE_WORLD,
        pbMsg);
    return singleMsg;
}

FGameSingleTLV UNetworkMessageFactoryUtil::MakeSkillTrigger(int pid, int skillId,int bulletId,const FGameMsgPack &position , const FGameMsgPack &velocity)
{
    auto &_position = static_cast<pb::Position&>(*position.msg);
    auto &_velocity = static_cast<pb::Velocity&>(*velocity.msg);
    auto pbMsg = new pb::SkillTrigger;
    pbMsg->set_pid(pid);
    pbMsg->set_skillid(skillId);
    pbMsg->set_bulletid(bulletId);
    auto p = pbMsg->mutable_p();
    p->CopyFrom(_position);
    auto v = pbMsg->mutable_v();
    v->CopyFrom(_velocity);

    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_SKILL_TRIGGER,
        pbMsg);
    return singleMsg;
}
FGameSingleTLV UNetworkMessageFactoryUtil::MakeSkillContact(int srcPid, int targetPid, int skillId, int bulletId, const FGameMsgPack& contactPosition)
{
    auto &_position = static_cast<pb::Position&>(*contactPosition.msg);
    auto pbMsg = new pb::SkillContact;
    pbMsg->set_srcpid(srcPid);
    pbMsg->set_targetpid(targetPid);
    pbMsg->set_skillid(skillId);
    pbMsg->set_bulletid(bulletId);
    auto p = pbMsg->mutable_contactpos();
    p->CopyFrom(_position);
    FGameSingleTLV singleMsg(
        GameMsgID_t::GAME_MSG_SKILL_CONTACT,
        pbMsg);
    return singleMsg;
}
