// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_ExplosiveBot.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "HA_Character.h"
#include "Weapons/HA_Weapon.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "Enemy/HA_Cannon.h"

AHA_ExplosiveBot::AHA_ExplosiveBot()
{
	ExplosionDamage = 100.0f;
	ExplosionRadius = 100.0f;
}

void AHA_ExplosiveBot::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		PlayerReference = Cast<AHA_Character>(PlayerPawn);
	}

	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_ExplosiveBot::Explode);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_ExplosiveBot::DamageTaken);

	NextPathPoint = GetNextPoint();

	if (IsValid(MyCannon))
	{
		FVector ForceDirection;
		ForceDirection = GetActorLocation() - MyCannon->GetActorLocation();
		MeshComponent->AddImpulse(ForceDirection * ShotStrenght, NAME_None, true);
	}
}

void AHA_ExplosiveBot::SelfDamage()
{
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), nullptr, nullptr);
}

void AHA_ExplosiveBot::SelfDestruct()
{
	if (bIsExploded)
	{
		return;
	}
	bIsExploded = true;

	if (IsValid(ExplosionEffect))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}
	TArray<AActor*> IgnoredActors;

	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);

	Destroy();
}

FVector AHA_ExplosiveBot::GetNextPoint()
{
	if (!IsValid(PlayerReference))
	{
		return GetActorLocation();
	}
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerReference);
	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	return GetActorLocation();
}

void AHA_ExplosiveBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarge = (NextPathPoint - GetActorLocation()).Size();
	if (DistanceToTarge <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPoint();
	}
	else {
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MovementSpeed;

		MeshComponent->AddForce(ForceDirection, NAME_None, true);
	}
}


void AHA_ExplosiveBot::Explode(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bCountdownStarted == true)
	{
		return;
	}

	if (OtherActor == PlayerReference)
	{
		bCountdownStarted = true;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SelfDamage, this, &AHA_ExplosiveBot::SelfDamage, 0.5f, true);
	}
}

void AHA_ExplosiveBot::DamageTaken(UHA_HealthComponent * ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
		UE_LOG(LogTemp, Log, TEXT("Valido"))
	}

	if (HealthComponent->IsDead())
	{
		if (IsValid(MyCannon))
		{
			MyCannon->SetIsBotAlived(false);
		}

		AHA_Weapon* Weapon = Cast<AHA_Weapon>(DamageCauser);
		if (IsValid(Weapon))
		{
			AHA_Character* DamagingActor = Cast<AHA_Character>(Weapon->GetOwner());
			if (IsValid(DamagingActor) && DamagingActor->GetCharacterType() == EHA_CharacterType::CharacterType_Player)
			{

			}
		}

		SelfDestruct();
	}
}
