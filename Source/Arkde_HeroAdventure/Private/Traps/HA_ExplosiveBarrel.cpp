// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/HA_ExplosiveBarrel.h"
#include "Components/BoxComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Core/HA_GameMode.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/Soundcue.h"

AHA_ExplosiveBarrel::AHA_ExplosiveBarrel()
{
	thisController = this->GetInstigatorController();
}

void AHA_ExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_ExplosiveBarrel::OnHitReceived);
}

void AHA_ExplosiveBarrel::OnHitReceived(UHA_HealthComponent * ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (IsValid(GameModeReference))
		{
			if (!bExploded)
			{
				bExploded = true;
				TArray<AActor*> IgnoredActors;
				UE_LOG(LogTemp, Warning, TEXT("KABOOM"))
				UGameplayStatics::ApplyRadialDamage(GetWorld(), TrapDamage, GetActorLocation(), DamageRadius, TrapDamageType, IgnoredActors, this, thisController);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrapEffect, GetActorLocation());

				if (IsValid(ExplosionSound))
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
				}
				GameModeReference->DestroySceneObject(this, 0.1f);
			}
		}
	}
}