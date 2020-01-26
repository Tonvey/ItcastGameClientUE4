// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldChatCenter.h"
#include "NetworkMessageFactoryUtil.h"
#include "NetworkController.h"

UWorldChatCenter::UWorldChatCenter()
{
}

UWorldChatCenter::~UWorldChatCenter()
{
}

void UWorldChatCenter::SendContent_Implementation(const FText& content)
{
    UE_LOG(LogTemp, Display, TEXT("UWorldChatCenter::SendContent_Implementation") );
	auto msg = UNetworkMessageFactoryUtil::MakeTalkContent(content);
	NetworkController::GetInstance().PushMsg(msg);
}
