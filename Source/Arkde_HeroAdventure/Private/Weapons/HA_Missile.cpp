// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Missile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Core/HA_GameMode.h"
#include "Arkde_HeroAdventure/Arkde_HeroAdventure.h"

// Sets default values
AHA_Missile::AHA_Missile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MissileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	MissileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MissileCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	MissileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = MissileCollision;
	
	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	MissileMesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 3000.0f;
	MovementComponent->MaxSpeed = 3000.0;

	HealthComponent = CreateDefaultSubobject<UHA_HealthComponent>(TEXT("HealthComponent"));

	thisController = this->GetInstigatorController();
}

// Called when the game starts or when spawned
void AHA_Missile::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	
	MissileCollision->OnComponentBeginOverlap.AddDynamic(this, &AHA_Missile::ExplosionTrigger);
}

// Called every frame
void AHA_Missile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHA_Missile::ExplosionTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	TArray<AActor*> IgnoredActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, ProjectileDamageType, IgnoredActors, this, thisController, true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	if (IsValid(GameModeReference))
	{
		GameModeReference->DestroySceneObject(this, 0.1f);
	}
}

