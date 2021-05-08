// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HA_Key.h"
#include "Components/StaticMeshComponent.h"
#include "HA_Character.h"
#include "Core/HA_GameMode.h"

AHA_Key::AHA_Key()
{
	//Component initialization
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMesh->SetupAttachment(RootComponent);
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Variable initialization
	Keytag = "KeyA";
}

//Executes functions related with the item the player picked up
void AHA_Key::PickUpItem(AHA_Character* PickupCharacter)
{
	Super::PickUpItem(PickupCharacter);
	if (IsValid(PickupCharacter) && PickupCharacter->GetCharacterType() == EHA_CharacterType::CharacterType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->AddKeyToCharacter(PickupCharacter, Keytag);
		}
	}
	Destroy();
}
