// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Shotgun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

AHA_Shotgun::AHA_Shotgun()
{
	TraceLenght = 500;
	MuzzleSocketName = "SCK_Muzzle";
}

void AHA_Shotgun::StartWeaponAction()
{
	Super::StartWeaponAction();

	FVector EyesLocation;
	FRotator EyesRotation;
	GetOwner()->GetActorEyesViewPoint(EyesLocation, EyesRotation);

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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Impact"));
	}
	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwner->GetMesh();
	if (IsValid(CharacterMeshComponent))
	{
		FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
		UGameplayStatics::SpawnEmitterAttached(ShootEffect, CurrentOwner->GetMesh(), MuzzleSocketName);
	}
}

void AHA_Shotgun::StopWeaponAction()
{
	Super::StopWeaponAction();
}
