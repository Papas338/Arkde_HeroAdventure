// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Shotgun.h"
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

void AHA_Shotgun::StartWeaponAction()
{
	Super::StartWeaponAction();

	GenerateShot(FVector(0, 0, 0));
}

void AHA_Shotgun::StopWeaponAction()
{
	Super::StopWeaponAction();
}

void AHA_Shotgun::GenerateShot(FVector Offset)
{

	FVector EyesLocation;
	FRotator EyesRotation;
	CurrentOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);

	FVector ShotDirection = EyesRotation.Vector();
	FVector TraceEnd = EyesLocation + (ShotDirection * TraceLenght);

	FHitResult HitResult;

	FCollisionQueryParams LineTraceQueryParams;
	LineTraceQueryParams.AddIgnoredActor(this);
	LineTraceQueryParams.AddIgnoredActor(GetOwner());
	LineTraceQueryParams.bTraceComplex = true;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyesLocation, TraceEnd, ECC_Visibility, LineTraceQueryParams);

	if (bHit)
	{
		TraceEnd = HitResult.ImpactPoint;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Impact"));
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			UGameplayStatics::ApplyPointDamage(HitActor, DamageDealt, ShotDirection, HitResult, CurrentOwner->GetInstigatorController(), this, DamageType);
		}

	}

	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwner->GetMesh();
	if (IsValid(CharacterMeshComponent))
	{
		FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);

		if (IsValid(TraceComponent))
		{
			TraceComponent->SetVectorParameter(TraceEffectName, TraceEnd);
		}
	}

	UGameplayStatics::SpawnEmitterAttached(ShootEffect, CurrentOwner->GetMesh(), MuzzleSocketName);


	if (bDrawLine)
	{
		DrawDebugLine(GetWorld(), EyesLocation, TraceEnd, FColor::Red, false, 1.0f, 0.0f, 1.0f);
	}
}
