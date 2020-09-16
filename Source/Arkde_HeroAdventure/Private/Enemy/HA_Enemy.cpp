// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Enemy.h"
#include "Camera/CameraComponent.h"
#include "Components/HA_HealthComponent.h"

AHA_Enemy::AHA_Enemy()
{
	
}

void AHA_Enemy::BeginPlay()
{
	Super::BeginPlay();


	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_Enemy::HealthChanged);
}

void AHA_Enemy::HealthChanged(UHA_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	
	if (HealthComponent->IsDead())
	{
		Destroy();
	}
	else
	{
		
	}
}