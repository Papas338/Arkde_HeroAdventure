// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_CannonsTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
AHA_CannonsTrigger::AHA_CannonsTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComponent"));
	RootComponent = HitBoxComponent;
	HitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AHA_CannonsTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_CannonsTrigger::ActiveCannons);
}

void AHA_CannonsTrigger::ActiveCannons(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCannonCollisionDelegate.Broadcast();
}

