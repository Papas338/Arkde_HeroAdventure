// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/HA_Landmine.h"
#include "Components/BoxComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Core/HA_GameMode.h"
#include "Arkde_HeroAdventure/Arkde_HeroAdventure.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AHA_Landmine::AHA_Landmine()
{
	AreaDetectionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AreaDetectionComponent"));
	AreaDetectionComponent->SetupAttachment(RootComponent);
	AreaDetectionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	AreaDetectionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	thisController = this->GetInstigatorController();
}

void AHA_Landmine::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_Landmine::OnHitReceived);
	AreaDetectionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Landmine::DetectionAlarm);
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Landmine::TrapActive);
}

void AHA_Landmine::OnHitReceived(UHA_HealthComponent * ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		if (!bExploded)
		{
			bExploded = true;
			TArray<AActor*> IgnoredActors;
			UGameplayStatics::ApplyRadialDamage(GetWorld(), TrapDamage, GetActorLocation(), DamageRadius, TrapDamageType, IgnoredActors, this, thisController, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrapEffect, GetActorLocation());

			if (IsValid(GameModeReference))
			{
				GameModeReference->DestroySceneObject(this, 0.1f);
			}
		}		
	}
}

void AHA_Landmine::DetectionAlarm(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("You are too close buddy"))
}

void AHA_Landmine::TrapActive(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	TArray<AActor*> IgnoredActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), TrapDamage, GetActorLocation(), DamageRadius, TrapDamageType, IgnoredActors, this, thisController, true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrapEffect, GetActorLocation());


	UE_LOG(LogTemp, Warning, TEXT("KABOOM"))
	if (IsValid(GameModeReference))
	{
		GameModeReference->DestroySceneObject(this, 0.1f);
	}
// 
// 	ACharacter* thisCharacter = Cast<ACharacter>(OtherActor);
// 	if (IsValid(thisCharacter))
// 	{
// 		thisCharacter->LaunchCharacter(FVector(0.0f, 150.0f, 0.0f),false,true);
// 	}
}

