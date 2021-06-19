// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::HandleDestruction()
{
	//Call base pawn class to play effects
	Super::HandleDestruction();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	FVector PlayerPawnLocation = PlayerPawn->GetActorLocation();

	RotateTurret(PlayerPawnLocation);
}

void APawnTurret::CheckFireCondition()
{
	//If Player == null || is dead then IGNORE firing (just bail)
	if (!PlayerPawn)
	{
		return;
	}
	//If Player is in range, fire
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}