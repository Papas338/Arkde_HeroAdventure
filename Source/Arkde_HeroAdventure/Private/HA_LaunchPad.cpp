// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HA_Character.h"

// Sets default values
AHA_LaunchPad::AHA_LaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitboxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxComponent"));
	HitboxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitboxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitboxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = HitboxComponent;

	LaunchPadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadComponent"));
	LaunchPadComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHA_LaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHA_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AHA_LaunchPad::JumpPadAction();
}

void AHA_LaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter)) {
			Player = OverlappedCharacter;
			bIsOverlapped = true;
			BP_Collision();
		}
	}
}

void AHA_LaunchPad::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter)) {
			BP_CollisionEnd();
			bIsOverlapped = false;
		}
	}
}

void AHA_LaunchPad::JumpPadAction()
{
	if (bIsOverlapped == false)
	{
		return;
	}
	if (Player->bIsDoingAction)
	{
		Player->LaunchCharacter(FVector(1000, 0, 1000), true, true);
	}
}


