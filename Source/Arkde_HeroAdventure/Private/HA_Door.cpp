// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HA_Character.h"

// Sets default values
AHA_Door::AHA_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;
	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorComponent"));
	DoorComponent->SetupAttachment(CustomRootComponent);
	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameComponent"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);
	OpenZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OpenZoneComponent"));
	OpenZoneComponent->SetupAttachment(CustomRootComponent);
	OpenZoneComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OpenZoneComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OpenZoneComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	angle = -90.0f;
	DoorTag = "KeyA";
}

// Called when the game starts or when spawned
void AHA_Door::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHA_Door::CheckKeyFromPlayer(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsOpen)
	{
		return;
	}
	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter))
		{
			if (OverlappedCharacter->HasKey(DoorTag))
			{
				OpenDoor();
			}
		}
	}
}


void AHA_Door::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Yep, definitely a door"));
	if (!bIsOpen)
	{
		OpenDoor();
		bIsOpen = true;
	}
	
}

void AHA_Door::OpenDoor()
{
	DoorComponent->AddRelativeRotation(FRotator(0, angle, 0));
}

// Called every frame
void AHA_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

