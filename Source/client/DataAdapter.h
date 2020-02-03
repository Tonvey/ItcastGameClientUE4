// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "proto/msg.pb.h"

/**
 * 
 */
class CLIENT_API DataAdapter
{
public:
	static pb::Position PostionCS(const FVector &_pos);
	static FVector PostionSC(const pb::Position &_pos);
	static FVector VelocitySC(const pb::Velocity &_vel);
	static pb::Velocity VelocityCS(const FVector &_pos);
private:
	DataAdapter();
	~DataAdapter();
};
