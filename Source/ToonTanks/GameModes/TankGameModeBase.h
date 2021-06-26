// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	int32 TurretAmount;

	int32 GetTurretAmount();

	void HandleGameStart();
	void HandleGameOver(bool bPlayerWon);

protected:
	virtual void BeginPlay() override;
UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);

public:
	void ActorDied(AActor* DiedActor);
};