// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//TODO 虽然其他头文件引入了GameMsg.h 但是不直接引入的话会导致UHT 工作不正常
#include "GameMsg.h"
#include "NetworkConnector.h"
#include "NetProtocolResolver.h"
#include "NetworkController.generated.h"
/**
 *
 */
UCLASS(BlueprintType)
class CLIENT_API UNetworkController : public UObject
{
	GENERATED_BODY()
public:
    static UNetworkController &GetInstance();
	UNetworkController();
	virtual ~UNetworkController();
    virtual void Init(FString ip , uint16 port);
    virtual void Finish();
    virtual void Reset();
    virtual void ProcessNetworkMessage();
    virtual void PushMsg(GameMsgArray_t &msg);
    UFUNCTION(BlueprintCallable)
    virtual void PushMsg(const FGameSingleTLV &msg);
    virtual void PauseProcessMessage();
    virtual void ResumeProcessMessage();
    bool IsPaused()const { return isPaused; };
    DECLARE_EVENT_TwoParams(UNetworkController, NewGameMessage,GameMsgID_t,::google::protobuf::Message*);
    virtual NewGameMessage &GetOnNewMessage(){return OnNewGameMessage;};
private:
    TSharedPtr<NetworkConnector> mConnector;
    TSharedPtr<NetProtocolResolver> mProtocol;
    NewGameMessage OnNewGameMessage;
    bool isPaused;
    GameMsgArray_t mLastMessages;
};
