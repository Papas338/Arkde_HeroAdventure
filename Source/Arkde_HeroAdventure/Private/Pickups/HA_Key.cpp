// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HA_Key.h"
#include "Components/StaticMeshComponent.h"
#include "HA_Character.h"

AHA_Key::AHA_Key()
{
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMesh->SetupAttachment(RootComponent);
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Keytag = "KeyA";
}

void AHA_Key::PickUpItem(AHA_Character* PickupActor)
{
	Super::PickUpItem(PickupActor);
	PickupActor->AddKey(Keytag);
	Destroy();
}
