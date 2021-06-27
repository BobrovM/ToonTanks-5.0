// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Get References And Win\Lose Conditions
	HandleGameStart();
}

int32 ATankGameModeBase::GetTurretAmount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT TurretActors);

	return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{
	TurretAmount = GetTurretAmount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerReference = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	//Initialise to start countdown, pointcounter and so on
	GameStart();
	if (PlayerControllerReference)
	{
		PlayerControllerReference->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerReference,
			&APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool bPlayerWon)
{
	//Win result if player killed all the turrets
	//Lose result if player died
	GameOver(bPlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DiedActor)
{
	//Check what died. If player, make losegame condition
	UE_LOG(LogTemp, Warning, TEXT("Actor died. Actor's name is %s"), *DiedActor->GetName());

	if (DiedActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerReference)
		{
			PlayerControllerReference->SetPlayerEnableState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DiedActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TurretAmount == 0)
		{
			HandleGameOver(true);
		}
	}
}