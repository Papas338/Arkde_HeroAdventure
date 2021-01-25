// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/HA_Bot.h"
#include "HA_HealingBot.generated.h"

class AHA_Enemy;
class USphereComponent;
class UHA_HealthComponent;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_HealingBot : public AHA_Bot
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Enemies")
		FVector EnemyLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
		float HealingAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
		float DamageReduction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies")
		TSubclassOf<AActor> EnemyClass;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<AActor*> EnemyArray;

	UPROPERTY(BlueprintReadOnly)
		AHA_Enemy* LowestHealthEnemy;

	UPROPERTY(BlueprintReadOnly)
		AHA_Enemy* EnemyHealed;

	UPROPERTY(BlueprintReadOnly, Category = "Healing")
		bool bIsHealing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
		bool bDebug;

	TSubclassOf<UDamageType> BotDamageType;

	FTimerHandle TimerHandle_Healing;

public:
	AHA_HealingBot();

protected:
	virtual void BeginPlay() override;

	void FindEnemies();

	UFUNCTION()
		void HealAlly(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void HealingStarted();

	void ActivateResistance();

	FVector GetNextPoint();

	UFUNCTION()
	void GettingDamaged(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		FVector LowestHealthEnemyPosition();

};
