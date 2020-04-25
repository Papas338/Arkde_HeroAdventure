// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HA_PickUp.h"
#include "Components/SphereComponent.h"
#include "HA_Character.h"

// Sets default values
AHA_PickUp::AHA_PickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitboxComponent"));
	HitBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = HitBoxComponent;
}

// Called when the game starts or when spawned
void AHA_PickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHA_PickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHA_PickUp::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter)) {
			PickUpItem(OverlappedCharacter);
		}
	}
}

void AHA_PickUp::PickUpItem(AHA_Character* PickupActor)
{
	BP_PickUp(PickupActor);
}