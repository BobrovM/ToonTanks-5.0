// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"


void ATankGameModeBase::BeginPlay()
{
	//Super::BeginPlay(); //Is it required?

	//Get References And Win\Lose Conditions

	//Call HandleGameStart() 
}

void ATankGameModeBase::HandleGameStart()
{
	//Initialise to start countdown, pointcounter and so on

	//Call BP GameStart
}

void ATankGameModeBase::HandleGameOver(bool bPlayerWon)
{
	//Win result if player killed all the turrets
	//Lose result if player died
	//Call BP GameOver
}

void ATankGameModeBase::ActorDied(AActor* DiedActor)
{
	//Check what died. If player, make losegame condition
}