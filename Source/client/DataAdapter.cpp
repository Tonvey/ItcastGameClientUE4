// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAdapter.h"
#define POSITION_UNIT_TRANSLATE_SCALE 100

pb::Position DataAdapter::PostionCS(FVector _pos)
{
    pb::Position ret;
    _pos /= POSITION_UNIT_TRANSLATE_SCALE;
    ret.set_z(_pos.X);
    ret.set_x(_pos.Y);
    ret.set_y(_pos.Z);
    return ret;
}

FVector DataAdapter::PostionSC(pb::Position _pos)
{
    FVector ret;
    ret.X = _pos.z();
    ret.Y= _pos.x();
    ret.Z = _pos.y();
    ret *= POSITION_UNIT_TRANSLATE_SCALE;
    return ret;
}

DataAdapter::DataAdapter()
{
}

DataAdapter::~DataAdapter()
{
}
