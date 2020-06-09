// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_UltimateCannon.h"
#include "Weapons/HA_Missile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AHA_UltimateCannon::AHA_UltimateCannon()
{
	UltimateSocketName = "SCK_Ultimate";
}

void AHA_UltimateCannon::StartWeaponAction()
{
	Super::StartWeaponAction();
	
	if (IsValid(CurrentWeaponOwner))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentWeaponOwner->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(UltimateSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(UltimateSocketName);

			AHA_Missile* CurrentMissile = GetWorld()->SpawnActor<AHA_Missile>(MissileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}
}

void AHA_UltimateCannon::StopWeaponAction()
{
	Super::StopWeaponAction();
}
