// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeReference = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InistigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		//Just wondering how Da faq this will be called but safety first
		UE_LOG(LogTemp, Error, TEXT("Shit got 0 health. Actor's name is %s"), *GetOwner()->GetName());
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

	if (Health <= 0)
	{
		if (GameModeReference)
		{
			GameModeReference->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Why the fuck did HealthComponent did not get the valid reference????? Owner of component is %s"),
				*GetOwner()->GetName());
		}
	}
}
