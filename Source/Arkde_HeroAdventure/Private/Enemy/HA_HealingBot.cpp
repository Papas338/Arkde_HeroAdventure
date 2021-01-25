// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_HealingBot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/HA_Enemy.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "HA_Character.h"

AHA_HealingBot::AHA_HealingBot()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsHealing = false;
}

void AHA_HealingBot::BeginPlay()
{
	Super::BeginPlay();

	FindEnemies();
	LowestHealthEnemy = Cast<AHA_Enemy>(EnemyArray[0]);

	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_HealingBot::HealAlly);
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_HealingBot::GettingDamaged);

	NextPathPoint = GetNextPoint();
}

void AHA_HealingBot::FindEnemies()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyArray);
}

FVector AHA_HealingBot::GetNextPoint()
{
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), LowestHealthEnemyPosition());
	if (NavPath->PathPoints.Num() > 1)
	{
		bIsHealing = true;
		return NavPath->PathPoints[1];
	}
	return GetActorLocation();
}

void AHA_HealingBot::GettingDamaged(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{

	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
		UE_LOG(LogTemp,Log,TEXT("Valido"))
	}

	if (HealthComponent->IsDead())
	{
		Destroy();
	}
}

void AHA_HealingBot::HealAlly(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EnemyHealed = Cast<AHA_Enemy>(OtherActor);
	if (IsValid(EnemyHealed) && EnemyHealed->GetCharacterType() != EHA_CharacterType::CharacterType_Player)
	{
		if ((EnemyHealed->HealthComponent->GetCurrentHealth() <= 100) && (EnemyHealed->GetCharacterType() == EHA_CharacterType::CharacterType_Enemy))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Healing, this, &AHA_HealingBot::HealingStarted, 1, true);
			UE_LOG(LogTemp, Log, TEXT("Sanacion"))
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Healing);
			UE_LOG(LogTemp, Log, TEXT("No sanacion"))
		}
	}

}

void AHA_HealingBot::HealingStarted()
{
	if (EnemyHealed->HealthComponent->GetCurrentHealth() >= 100)
	{
		bIsHealing = false;
		return;
	}
	TArray<AActor*> IgnoredActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), -HealingAmount, GetActorLocation(), 100, BotDamageType, IgnoredActors, this, GetInstigatorController(), true);
	UE_LOG(LogTemp, Log, TEXT("Healing"))
}

void AHA_HealingBot::ActivateResistance()
{
	for (AActor* SelectedActor : EnemyArray)
	{
		AHA_Enemy* Enemy = Cast<AHA_Enemy>(SelectedActor);
		if (IsValid(Enemy))
		{
			Enemy->HealthComponent->SetBotAffected(!bIsHealing, DamageReduction);
		}
	}
}

void AHA_HealingBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindEnemies();
	ActivateResistance();

	float DistanceToTarget = (NextPathPoint - GetActorLocation()).Size();
	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPoint();
	}
	else {
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MovementSpeed;
		MeshComponent->AddForce(ForceDirection, NAME_None, true);
	}
}

FVector AHA_HealingBot::LowestHealthEnemyPosition()
{
	if (EnemyArray.Num() != 0)
	{
		for (int i = 0; i < EnemyArray.Num(); i++)
		{
			AHA_Enemy* Enemy = Cast<AHA_Enemy>(EnemyArray[i]);

			if (IsValid(Enemy) && IsValid(LowestHealthEnemy))
			{
				float Enemy1Health = Enemy->HealthComponent->GetCurrentHealth();
				float LowestHealth = LowestHealthEnemy->HealthComponent->GetCurrentHealth();
				if (Enemy1Health < LowestHealth)
				{
					LowestHealthEnemy = Enemy;
				}
			}
		}
		if (IsValid(LowestHealthEnemy))
		{
			if (LowestHealthEnemy->HealthComponent->GetCurrentHealth() != 100 && LowestHealthEnemy->HealthComponent->GetCurrentHealth() != 0)
			{
				return LowestHealthEnemy->GetActorLocation();
			}
		}
		else
		{
			LowestHealthEnemy = Cast<AHA_Enemy>(EnemyArray[0]);
		}
	}

	return GetActorLocation();
}

