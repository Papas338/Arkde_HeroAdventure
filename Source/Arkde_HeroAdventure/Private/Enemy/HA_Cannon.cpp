// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "HA_Character.h"
#include "Enemy/HA_Bot.h"
#include "Enemy/HA_ExplosiveBot.h"

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
}

// Called when the game starts or when spawned
void AHA_Cannon::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerReference = Cast<AHA_Character>(PlayerPawn);
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
	FVector ShotOrigin = ShotLocation->GetComponentLocation();
	FTransform BotTransform = FTransform(FRotator::ZeroRotator, ShotOrigin);
	AHA_Bot* NewBot = GetWorld()->SpawnActorDeferred<AHA_Bot>(BotToShoot, BotTransform);
	if (IsValid(NewBot))
	{
		AHA_ExplosiveBot* ExplosiveBot = Cast<AHA_ExplosiveBot>(NewBot);
		if (IsValid(ExplosiveBot))
		{
			ExplosiveBot->SetMyCannon(this);
		}
	}
	NewBot->FinishSpawning(BotTransform);

	
}

void AHA_Cannon::RotateCannon()
{
	PlayerPosition = GetActorLocation() - PlayerReference->GetActorLocation();
	PointingDirection = UKismetMathLibrary::MakeRotFromX(PlayerPosition);
	PointingDirection.Pitch += 45;
	SetActorRotation(PointingDirection);
}
