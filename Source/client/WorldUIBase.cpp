// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldUIBase.h"
#include "GameEventDispatcher.h"

UWorldUIBase::UWorldUIBase(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
}
UWorldUIBase::~UWorldUIBase()
{
}

bool UWorldUIBase::Initialize()
{
	bool ret = Super::Initialize();
	if (ret)
	{
		//int,std::string,std::string
		mHandler = UGameEventDispatcher::GetInstance()->GetOnSyncChat().AddLambda
		(
			[this](int _pid, std::string _name, std::string _content)
			{
				auto name = UTF8_TO_TCHAR(_name.c_str());
				auto content = UTF8_TO_TCHAR(_content.c_str());
				this->OnNewChatMessage(_pid, name, content);
			}
		);
	}
	return ret;
}

void UWorldUIBase::BeginDestroy()
{
	Super::BeginDestroy();
	if (mHandler.IsValid())
	{
		UGameEventDispatcher::GetInstance()->GetOnSyncChat().Remove(mHandler);
	}
}
