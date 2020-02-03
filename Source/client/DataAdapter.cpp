// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAdapter.h"
#define POSITION_UNIT_TRANSLATE_SCALE 100

pb::Position DataAdapter::PostionCS(const FVector &_pos)
{
    pb::Position ret;
    auto pos = _pos;
    pos /= POSITION_UNIT_TRANSLATE_SCALE;
    ret.set_z(pos.X);
    ret.set_x(pos.Y);
    ret.set_y(pos.Z);
    return ret;
}

FVector DataAdapter::PostionSC(const pb::Position &_pos)
{
    FVector ret;
    ret.X = _pos.z();
    ret.Y= _pos.x();
    ret.Z = _pos.y();
    ret *= POSITION_UNIT_TRANSLATE_SCALE;
    return ret;
}

FVector DataAdapter::VelocitySC(const pb::Velocity &_vel)
{
    FVector ret;
    ret.X = _vel.z();
    ret.Y = _vel.x();
    ret.Z = _vel.y();
    ret *= POSITION_UNIT_TRANSLATE_SCALE;
    return ret;
}

pb::Velocity DataAdapter::VelocityCS(const FVector &_pos)
{
    pb::Velocity ret;
    auto pos = _pos;
    pos /= POSITION_UNIT_TRANSLATE_SCALE;
    ret.set_z(pos.X);
    ret.set_x(pos.Y);
    ret.set_y(pos.Z);
    return ret;
}

DataAdapter::DataAdapter()
{
}

DataAdapter::~DataAdapter()
{
}
