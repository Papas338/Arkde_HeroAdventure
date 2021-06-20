// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_WeaponSpawner.h"
#include "HA_Character.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/HA_GameMode.h"

// Sets default values
AHA_WeaponSpawner::AHA_WeaponSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSpawnerComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitBoxComponent"));
	RootComponent = WeaponSpawnerComponent;
	WeaponSpawnerComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

	WSHitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("WSHitBoxComponent"));
	WSHitBoxComponent->SetupAttachment(RootComponent);
	WSHitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	WSHitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AHA_WeaponSpawner::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	
	WSHitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_WeaponSpawner::PlayerEnterOverlap);
	WSHitBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHA_WeaponSpawner::PlayerExitOverlap);
}

// Called every frame
void AHA_WeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GiveWeapon();
}

void AHA_WeaponSpawner::PlayerEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsPlayerOverlapping = true;
	GameModeReference->PickUpOverlap(bIsPlayerOverlapping);
	OverlappingPlayer = Cast<AHA_Character>(OtherActor);
}

void AHA_WeaponSpawner::PlayerExitOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsPlayerOverlapping = false;
	GameModeReference->PickUpOverlap(bIsPlayerOverlapping);
}

void AHA_WeaponSpawner::GiveWeapon()
{
	if (!bIsPlayerOverlapping)
	{
		return;
	}
	if (OverlappingPlayer->bIsDoingAction && !OverlappingPlayer->bIsAiming)
	{
		OverlappingPlayer->SetFireWeaponClass(WeaponToDisplay);
		OverlappingPlayer->SetSecondaryWeapon();
		Destroy();
	}
}


