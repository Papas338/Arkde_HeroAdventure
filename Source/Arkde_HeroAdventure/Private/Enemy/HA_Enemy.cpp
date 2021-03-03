// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Enemy.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "Enemy/Controller/HS_AIControllerNew.h"
#include "Camera/CameraComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Weapons/HA_Weapon.h"

AHA_Enemy::AHA_Enemy()
{
}

void AHA_Enemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_Enemy::HealthChanged);
	MyController = Cast<AHS_AIControllerNew>(GetController());
	
}

void AHA_Enemy::HealthChanged(UHA_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!IsValid(MyController))
	{
		return;
	}

	if (HealthComponent->IsDead())
	{
		MyController->UnPossess();
	}
	else
	{
		AHA_Weapon* PlayerWeapon = Cast<AHA_Weapon>(DamageCauser);
		if (IsValid(PlayerWeapon))
		{
			MyController->SetReceivingDamage(true);
			AActor* RifleOwner = PlayerWeapon->GetOwner();
			UAISense_Damage::ReportDamageEvent(GetWorld(), this, RifleOwner, Damage, RifleOwner->GetActorLocation(), FVector::ZeroVector);
		}
	}
}