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

	bIsHealing = false;
}

// Called when the game starts or when spawned
void AHA_Bot::BeginPlay()
{
	Super::BeginPlay();
	
	FindEnemies();
	LowestHealthEnemy = Cast<AHA_Enemy>(EnemyArray[0]);

	NextPathPoint = GetNextPoint();

	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Bot::HealAlly);
}

void AHA_Bot::FindEnemies()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyArray);
		
}

FVector AHA_Bot::GetNextPoint()
{
 	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), LowestHealthEnemyPosition());
 	if (NavPath->PathPoints.Num() > 1)
 	{
 		return NavPath->PathPoints[1];
 	}
	return GetActorLocation();
}

void AHA_Bot::HealAlly(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EnemyHealed = Cast<AHA_Enemy>(OtherActor);
	if (IsValid(EnemyHealed))
	{
		if ((EnemyHealed->HealthComponent->GetCurrentHealth() <= 100) && (EnemyHealed->GetCharacterType() == EHA_CharacterType::CharacterType_Enemy))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Healing, this, &AHA_Bot::HealingStarted, 1, true);
			UE_LOG(LogTemp, Log, TEXT("Sanacion"))
				bIsHealing = true;
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Healing);
			UE_LOG(LogTemp, Log, TEXT("No sanacion"))
		}
	}
	
}

void AHA_Bot::HealingStarted()
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

void AHA_Bot::ActivateResistance()
{
	for (AActor* SelectedActor : EnemyArray)
	{
		AHA_Enemy* Enemy = Cast<AHA_Enemy>(SelectedActor);
		if (IsValid(Enemy))
		{
			Enemy->HealthComponent->SetBotAffected(!bIsHealing);
		}
	}
}

// Called every frame
void AHA_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FindEnemies();
	ActivateResistance();
	float DistanceToTarget = (NextPathPoint - GetActorLocation()).Size();
	if (DistanceToTarget <= MinDistanceToEnemy)
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

FVector AHA_Bot::LowestHealthEnemyPosition()
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
	return GetActorLocation();
}


