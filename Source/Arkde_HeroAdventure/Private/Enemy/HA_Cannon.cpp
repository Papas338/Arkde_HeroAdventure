// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Core/HA_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "HA_Character.h"
#include "Enemy/HA_Bot.h"
#include "Enemy/HA_CannonsTrigger.h"
#include "Enemy/HA_ExplosiveBot.h"
#include "Sound/Soundcue.h"

// Sets default values
AHA_Cannon::AHA_Cannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CannonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMeshComponent"));
	RootComponent = CannonMeshComponent;
	CannonMeshComponent->SetCanEverAffectNavigation(false);

	HitBoxComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBoxComponent"));
	HitBoxComponent->SetupAttachment(CannonMeshComponent);

	ShotLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ShootLocationComponent"));
	ShotLocation->SetupAttachment(CannonMeshComponent);

	bIsCannonActive = false;
	bIsBotAlived = false;
}

// Called when the game starts or when spawned
void AHA_Cannon::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerReference = Cast<AHA_Character>(PlayerPawn);

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());

	GameModeReference->OnEnemyKilledDelegate.AddDynamic(this, &AHA_Cannon::DeactivateCannon);

	AActor* CannonTriggerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AHA_CannonsTrigger::StaticClass());
	if (IsValid(CannonTriggerActor))
	{
		CannonTriggerReference = Cast<AHA_CannonsTrigger>(CannonTriggerActor);
		CannonTriggerReference->OnCannonCollisionDelegate.AddDynamic(this, &AHA_Cannon::ActivateCannon);
	}
}

// Called every frame
void AHA_Cannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCannon();

	ShootBot();
}

void AHA_Cannon::ShootBot()
{
	if (!bIsCannonActive) {
		return;
	}
	if (bIsBotAlived == false)
	{
		FVector ShotOrigin = ShotLocation->GetComponentLocation();
		FTransform BotTransform = FTransform(FRotator::ZeroRotator, ShotOrigin);
		AHA_Bot* NewBot = GetWorld()->SpawnActorDeferred<AHA_Bot>(BotToShoot, BotTransform);
		if (IsValid(NewBot))
		{
			AHA_ExplosiveBot* ExplosiveBot = Cast<AHA_ExplosiveBot>(NewBot);
			if (IsValid(ExplosiveBot))
			{
				SetIsBotAlived(true);
				ExplosiveBot->SetMyCannon(this);
			}
		}
		NewBot->FinishSpawning(BotTransform);

		if (IsValid(ShotSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSound, GetActorLocation());
		}
	}	
}

void AHA_Cannon::RotateCannon()
{
	if (!bIsCannonActive) 
	{
		return;
	}
	PlayerPosition = GetActorLocation() - PlayerReference->GetActorLocation();
	PointingDirection = UKismetMathLibrary::MakeRotFromX(PlayerPosition);
	PointingDirection.Pitch += CannonAngle;
	SetActorRotation(PointingDirection);
}

void AHA_Cannon::ActivateCannon()
{
	bIsCannonActive = true;
}

void AHA_Cannon::DeactivateCannon(float EnemiesKilled)
{
	if (EnemiesKilled == 7) {
		bIsCannonActive = false;
	}
}

