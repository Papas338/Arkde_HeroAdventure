// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_VictoryZone.h"
#include "Components/BoxComponent.h"
#include "Core/HA_GameMode.h"
#include "HA_Character.h"

// Sets default values
AHA_VictoryZone::AHA_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;
	VictoryZoneComponent->SetBoxExtent(FVector(50.0f));
}

// Called when the game starts or when spawned
void AHA_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AHA_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHA_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IsValid(GameModeReference) && IsValid(OtherActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(PlayerCharacter))
		{
			GameModeReference->Victory(PlayerCharacter);
		}
	}
}

