// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/HA_Trap.h"
#include "HA_ExplosiveBarrel.generated.h"

class AHA_GameMode;
class AController;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_ExplosiveBarrel : public AHA_Trap
{
	GENERATED_BODY()

//Variables
protected:
	AHA_GameMode* GameModeReference;

	AController* thisController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trap")
		float DamageRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Trap")
		bool bExploded;

public:
	// Sets default values for this actor's properties
	AHA_ExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHitReceived(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);
};
