// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HA_KeySpawner.h"
#include "Core/HA_GameMode.h"
#include "Components/Billboardcomponent.h"
#include "Enemy/HA_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/HA_Key.h"

// Sets default values
AHA_KeySpawner::AHA_KeySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnerBillboardComponent"));
	RootComponent = SpawnerBillboardComponent;
}

// Called when the game starts or when spawned
void AHA_KeySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());

	GameModeReference->OnEnemyKilledDelegate.AddDynamic(this, &AHA_KeySpawner::SpawnKey);
}

void AHA_KeySpawner::SpawnKey(float EnemiesKilled)
{
	if (bHasSpawned || EnemiesKilled < 2)
	{
		return;
	}
	FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
	KeySpawned = GetWorld()->SpawnActorDeferred<AHA_Key>(KeyClass, SpawnTransform, this, nullptr);
	KeySpawned->SetKeyTag("KeyA");
	UGameplayStatics::FinishSpawningActor(KeySpawned, SpawnTransform);
	bHasSpawned = true;
	BP_SpawnKey();
}

// Called every frame
void AHA_KeySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}