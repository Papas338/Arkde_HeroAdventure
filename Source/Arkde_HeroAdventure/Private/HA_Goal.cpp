// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_Goal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AHA_Goal::AHA_Goal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GoalHitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxComponent"));
	GoalHitBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalHitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	GoalHitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = GoalHitBoxComponent;
	GoalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalMeshComponent"));
	GoalMeshComponent->SetupAttachment(RootComponent);
	GoalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AHA_Goal::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHA_Goal::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	GoalReached();
}

// Called every frame
void AHA_Goal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHA_Goal::GoalReached()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Goal Reached!"));
}