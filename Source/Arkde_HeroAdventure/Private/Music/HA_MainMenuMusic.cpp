// Fill out your copyright notice in the Description page of Project Settings.


#include "Music/HA_MainMenuMusic.h"
#include "Components/BillboardComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AHA_MainMenuMusic::AHA_MainMenuMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillboardComponent"));
	RootComponent = MusicBillboardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));

}

