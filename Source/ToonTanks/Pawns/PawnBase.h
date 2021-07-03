// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Camera/CameraShakeBase.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class AProjectileBase;
class UCapsuleComponent;
class UHealthComponent;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	virtual void HandleDestruction();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UCameraShakeBase> DeathShake;

protected:

	void RotateTurret(FVector TargetLocation);

	void Fire();
};