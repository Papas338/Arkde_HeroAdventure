// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/HA_Trap.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AHA_Trap::AHA_Trap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrapMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMeshComponent"));
	RootComponent = TrapMeshComponent;

	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComponent"));
	HitBoxComponent->SetupAttachment(RootComponent);
	HitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	HealthComponent = CreateDefaultSubobject<UHA_HealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AHA_Trap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHA_Trap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHA_Trap::TrapActive(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

