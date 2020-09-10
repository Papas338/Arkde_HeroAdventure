// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Bot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/HA_Enemy.h"

// Sets default values
AHA_Bot::AHA_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitboxComponent"));
	RootComponent = HitBoxComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(HitBoxComponent);

	HealthComponent = CreateDefaultSubobject<UHA_HealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AHA_Bot::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AHA_Bot::FindEnemies()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, EnemyArray);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BotClass, BotArray);
	
	for (int i=0; i <BotArray.Num();i++)
	{
		AHA_Bot* Bot = Cast<AHA_Bot>(BotArray[i]);
		if (GetCharacterType() == EHA_BotType::BotType_Enemy)
		{
			EnemyArray.Add(BotArray[i]);
		}
	}
	
}

// Called every frame
void AHA_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindEnemies();
}

FVector AHA_Bot::LowestHealthEnemyPosition()
{
	int EnemyNumber = 0;
	float Enemy1Health = 0;
	float Enemy2Health = 0;

	for (int i = 0; i < EnemyArray.Num(); i++)
 	{
		if ((i + 1) < EnemyArray.Num())
		{
			if (IsValid(Cast<AHA_Enemy>(EnemyArray[i])))
			{
				AHA_Enemy* Enemy = Cast<AHA_Enemy>(EnemyArray[i]);
				Enemy1Health = Enemy->HealthComponent->GetCurrentHealth();
			}
			else if (IsValid(Cast<AHA_Bot>(EnemyArray[i])))
			{
				AHA_Bot* Enemy = Cast<AHA_Bot>(EnemyArray[i]);
				Enemy1Health = Enemy->HealthComponent->GetCurrentHealth();
			}

			if (IsValid(Cast<AHA_Enemy>(EnemyArray[i + 1])))
			{
				AHA_Enemy* Enemy2 = Cast<AHA_Enemy>(EnemyArray[i + 1]);
				Enemy2Health = Enemy2->HealthComponent->GetCurrentHealth();
			}
			else if (IsValid(Cast<AHA_Bot>(EnemyArray[i + 1])))
			{
				AHA_Bot* Enemy2 = Cast<AHA_Bot>(EnemyArray[i + 1]);
				Enemy2Health = Enemy2->HealthComponent->GetCurrentHealth();
			}
 
			if (Enemy1Health < Enemy2Health)
			{
				EnemyNumber = i;
			}
			else
			{
				EnemyNumber = i + 1;
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Enemy selected: %d"), EnemyNumber)

//	float LowestHealth;

 	if (IsValid(Cast<AHA_Enemy>(EnemyArray[EnemyNumber])))
 	{
// 		AHA_Enemy* LowestHealthEnemy = Cast<AHA_Enemy>(EnemyArray[EnemyNumber]);
// 		LowestHealth = LowestHealthEnemy->HealthComponent->GetCurrentHealth();
// 		
// 		if (LowestHealth != 100)
// 		{
// 			return LowestHealthEnemy->GetActorLocation();
// 		}
 	}
// 	else if (IsValid(Cast<AHA_Bot>(EnemyArray[EnemyNumber])))
// 	{
// 		AHA_Bot* LowestHealthEnemy = Cast<AHA_Bot>(EnemyArray[EnemyNumber]);
// 		LowestHealth = LowestHealthEnemy->HealthComponent->GetCurrentHealth();
// 		
// 		if (LowestHealth != 100)
// 		{
// 			return LowestHealthEnemy->GetActorLocation();
// 		}
// 	}
	return GetActorLocation();
}


