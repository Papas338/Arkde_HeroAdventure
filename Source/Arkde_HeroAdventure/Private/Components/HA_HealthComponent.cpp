// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HA_HealthComponent.h"

UHA_HealthComponent::UHA_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHA_HealthComponent::DamageTaken);
	}
}

void UHA_HealthComponent::DamageTaken(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (bBotActive)
	{
		Damage /= 0.8;
		UE_LOG(LogTemp, Log, TEXT("Damage applied: %s"), *FString::SanitizeFloat(Damage))
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	if (CurrentHealth == 0.0)
	{
		bIsDead = true;
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("My health is: %s"), *FString::SanitizeFloat(CurrentHealth))
	}
}

void UHA_HealthComponent::SetBotAffected(bool bIsAffected)
{
	bBotActive = bIsAffected;
}
