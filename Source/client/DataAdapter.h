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
	static pb::Position PostionCS(FVector _pos);
	static FVector PostionSC(pb::Position _pos);
private:
	DataAdapter();
	~DataAdapter();
};
