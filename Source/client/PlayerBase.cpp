// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "GameEventDispatcher.h"
#include <stdexcept>

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
    GameEventDispatcher::GetInstance();
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerBase::SetPid(int _pid)
{
    this->mPid = _pid;
    this->mOnSetPid.Broadcast(_pid);
}
void APlayerBase::SetPlayerName(std::string _playerName)
{
    mPlayerName = UTF8_TO_TCHAR(_playerName.c_str());
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    if (this->mPlayerNameTextComp != nullptr)
    {
		this->mPlayerNameTextComp->SetText(mPlayerName);
    }
}
void APlayerBase::SetPlayerName(FString _playerName)
{
    mPlayerName = _playerName;
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    if (this->mPlayerNameTextComp != nullptr)
    {
		this->mPlayerNameTextComp->SetText(mPlayerName);
    }
}

void APlayerBase::SetPosition(int _pid, pb::Position _pos)
{
    throw std::runtime_error("Not implemented!");
}
