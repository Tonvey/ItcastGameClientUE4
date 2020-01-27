// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "GameEventDispatcher.h"
#include "DataAdapter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}
void APlayerBase::SetPlayerName(std::string _playerName)
{
    mPlayerName = UTF8_TO_TCHAR(_playerName.c_str());
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    this->UpdateUIName(mPlayerName);
}
void APlayerBase::SetHP(int _hp)
{
    this->HP = _hp;
    this->UpdateUIHp(1000,HP);
}
void APlayerBase::SetPlayerName_Implementation(const FString &_playerName)
{
    mPlayerName = _playerName;
    this->mOnSetPlayerName.Broadcast(mPlayerName);
    this->UpdateUIName(mPlayerName);
}
FVector APlayerBase::Ground2Pivot(const FVector ground) const
{
    return FVector(ground.X, ground.Y, ground.Z + this->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

FVector APlayerBase::Pivot2Ground(const FVector pivot) const
{
    return FVector(pivot.X, pivot.Y, pivot.Z - this->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

void APlayerBase::SetPlayerGroundLocation(const FVector &_pos)
{
    this->SetActorLocation(Ground2Pivot(_pos));
}

FVector APlayerBase::GetPlayerGroundLocation()const
{
    return Pivot2Ground(this->GetActorLocation());
}

void APlayerBase::SetDirection(float _zRot)
{
    FQuat rot = FQuat::MakeFromEuler(FVector(0, 0, _zRot));
    this->SetActorRotation(rot);
}

void APlayerBase::SetPlayerGroundLocation(int _pid, pb::Position _pos)
{
    if (_pid != mPid)
    {
        return;
    }
    auto location = DataAdapter::PostionSC(_pos);
    UE_LOG(LogTemp, Display, TEXT("PlayerBase::SetPlayerGroundLocation x:%f y:%f z:%f"),location.X,location.Y,location.Z);
    this->SetPlayerGroundLocation(location);
    this->SetHP(_pos.bloodvalue());
    this->SetDirection(_pos.v());
}

pb::Position APlayerBase::GetPosition() const
{
    auto location = this->GetPlayerGroundLocation();
    pb::Position pos = DataAdapter::PostionCS(location);
    auto rot = this->GetActorRotation();
    pos.set_v(rot.Euler().Z);
    pos.set_bloodvalue(this->HP);
    return pos;
}

FGameMsgPack APlayerBase::GetPositionPack() const
{
    auto pos = new pb::Position(GetPosition());
    return { pos };
}
