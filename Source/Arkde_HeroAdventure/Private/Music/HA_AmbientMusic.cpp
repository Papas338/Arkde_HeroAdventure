// Fill out your copyright notice in the Description page of Project Settings.


#include "Music/HA_AmbientMusic.h"
#include "Components/BillboardComponent.h"
#include "Components/AudioComponent.h"
#include "Core/HA_GameMode.h"

// Sets default values
AHA_AmbientMusic::AHA_AmbientMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillboardComponent"));
	RootComponent = MusicBillboardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));

	AlertParamName = "Maze";
}

// Called when the game starts or when spawned
void AHA_AmbientMusic::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &AHA_AmbientMusic::StopLevelMusic);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &AHA_AmbientMusic::StopLevelMusic);
		GameModeReference->OnMapZoneChangeDelegate.AddDynamic(this, &AHA_AmbientMusic::ChangeLevelMusic);
	}
}

void AHA_AmbientMusic::StopLevelMusic()
{
	MusicAudioComponent->Stop();
}

void AHA_AmbientMusic::ChangeLevelMusic(bool bIsAlertMode)
{
	MusicAudioComponent->SetBoolParameter(AlertParamName, bIsAlertMode);
}


