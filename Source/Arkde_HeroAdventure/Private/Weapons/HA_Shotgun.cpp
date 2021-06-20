// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Shotgun.h"
#include "Arkde_HeroAdventure/Arkde_HeroAdventure.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

AHA_Shotgun::AHA_Shotgun()
{
	TraceLenght = 500;
	MuzzleSocketName = "SCK_Muzzle";
	DamageDealt = 1.0f;
}

//Executes functions related with the weapon shooting
void AHA_Shotgun::StartWeaponAction()
{
	Super::StartWeaponAction();
	if (bIsOnCooldown)
	{
		return;
	}
	bIsOnCooldown = true;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_WeaponFireRate);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_WeaponFireRate, this, &AHA_Weapon::ResetCooldown, WeaponFireRate, false);

	GenerateShot(FVector(0, 0, 0));
	GenerateShot(FVector(0, 40, 0));
	GenerateShot(FVector(0, -40, 0));
	GenerateShot(FVector(0, 0, 40));
	GenerateShot(FVector(0, 0, -40));
}

//Executes functions when the player stops shooting
void AHA_Shotgun::StopWeaponAction()
{
	Super::StopWeaponAction();
}

//Generates everything related with the shot, such as the damage dealer and particles that create a visual representation of it
void AHA_Shotgun::GenerateShot(FVector Offset)
{
	FVector EyesLocation;
	FRotator EyesRotation;
	CurrentWeaponOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);

	FVector ShotDirection = EyesRotation.Vector();
	FVector TraceEnd = EyesLocation + (ShotDirection * TraceLenght) + Offset;

	FHitResult HitResult;

	FCollisionQueryParams LineTraceQueryParams;
	LineTraceQueryParams.AddIgnoredActor(this);
	LineTraceQueryParams.AddIgnoredActor(GetOwner());
	LineTraceQueryParams.bTraceComplex = true;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyesLocation, TraceEnd, COLLISION_WEAPON, LineTraceQueryParams);

	if (bHit)
	{
		TraceEnd = HitResult.ImpactPoint;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Impact"));
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			UGameplayStatics::ApplyPointDamage(HitActor, DamageDealt, ShotDirection, HitResult, CurrentWeaponOwner->GetInstigatorController(), this, DamageType);
		}

	}

	USkeletalMeshComponent* CharacterMeshComponent = CurrentWeaponOwner->GetMesh();
	if (IsValid(CharacterMeshComponent))
	{
		FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);

		if (IsValid(TraceComponent))
		{
			TraceComponent->SetVectorParameter(TraceEffectName, TraceEnd);
		}
	}

	UGameplayStatics::SpawnEmitterAttached(ShootEffect, CurrentWeaponOwner->GetMesh(), MuzzleSocketName);


	if (bDrawLine)
	{
		DrawDebugLine(GetWorld(), EyesLocation, TraceEnd, FColor::Red, false, 1.0f, 0.0f, 1.0f);
	}
}

