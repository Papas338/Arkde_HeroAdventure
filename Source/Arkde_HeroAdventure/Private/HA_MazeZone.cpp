// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_MazeZone.h"
#include "Components/BoxComponent.h"
#include "Core/HA_GameMode.h"

// Sets default values
AHA_MazeZone::AHA_MazeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxComponent"));
	HitBoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHA_MazeZone::BeginPlay()
{
	Super::BeginPlay();
	
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_MazeZone::EnterZone);
	HitBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHA_MazeZone::ExitZone);

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
}

void AHA_MazeZone::EnterZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsInZone = true;
	GameModeReference->CheckAlerts();
}

void AHA_MazeZone::ExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsInZone = false;
	GameModeReference->CheckAlerts();
}


