// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Bot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/HA_Enemy.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "HA_Character.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/AudioComponent.h"
#include "Sound/Soundcue.h"


// Sets default values
AHA_Bot::AHA_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);
	MeshComponent->SetSimulatePhysics(true);

	RootComponent = MeshComponent;

	HitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitboxComponent"));
	HitBoxComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHA_HealthComponent>(TEXT("HealthComponent"));

	TickSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TickSoundComponent"));
	TickSoundComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHA_Bot::BeginPlay()
{
	Super::BeginPlay();

	BotMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComponent->GetMaterial(0));
}

void AHA_Bot::PlayTimerSound()
{
	TickSoundComponent->Play();
}

void AHA_Bot::PlayExplosionSound()
{
	if (!IsValid(ExplosionSound))
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
}



// Called every frame
void AHA_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


