// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_Goal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AHA_Goal::AHA_Goal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components initialization
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

// Called every frame
void AHA_Goal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Detects if the player has reached the goal
void AHA_Goal::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	GoalReached();
}

//Runs different functions when the Goal is reached
void AHA_Goal::GoalReached()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Goal Reached!"));
}