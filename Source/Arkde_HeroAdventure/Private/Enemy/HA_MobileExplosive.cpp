// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_MobileExplosive.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "DrawDebugHelpers.h"
#include "HA_Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Particles/ParticleSystem.h"
#include "Weapons/HA_Weapon.h"

// Sets default values
AHA_MobileExplosive::AHA_MobileExplosive()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMeshComponent"));
	ExplosiveMesh->SetCanEverAffectNavigation(false);
	ExplosiveMesh->SetSimulatePhysics(true);
	RootComponent = ExplosiveMesh;

	HitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxComponent"));
	HitBoxComponent->SetupAttachment(ExplosiveMesh);
	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(ExplosiveMesh);

	HealthComponent = CreateDefaultSubobject<UHA_HealthComponent>(TEXT("HealthComponent"));
	
	ExplosionDamage = 100.0f;
	ExplosionRadius = 100.0f;
}

// Called when the game starts or when spawned
void AHA_MobileExplosive::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		PlayerReference = Cast<AHA_Character>(PlayerPawn);
	}
	
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_MobileExplosive::Explode);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_MobileExplosive::DamageTaken);

	NextPathPoint = GetNextPathPoint();
}

// Called every frame
void AHA_MobileExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarge = (NextPathPoint - GetActorLocation()).Size();
	if (DistanceToTarge <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else {
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;

		ExplosiveMesh->AddForce(ForceDirection, NAME_None, true);
	}
}

FVector AHA_MobileExplosive::GetNextPathPoint()
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

void AHA_MobileExplosive::SelfDamage()
{
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), nullptr, nullptr);
}

void AHA_MobileExplosive::SelfDestruct()
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

void AHA_MobileExplosive::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bCountdownStarted == true)
	{
		return;
	}

	if (OtherActor == PlayerReference)
	{
		bCountdownStarted = true;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SelfDamage, this, &AHA_MobileExplosive::SelfDamage, 0.5f, true);
	}
}

void AHA_MobileExplosive::DamageTaken(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HealthComponent->IsDead())
	{
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