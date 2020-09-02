// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HA_Weapon.h"
#include "HA_Sniper.generated.h"

class UParticleSystem;

/**
 *
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Sniper : public AHA_Weapon
{
	GENERATED_BODY()

protected:
	//variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Linetrace")
		float TraceLenght;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Linetrace")
		bool bDrawLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		FName TraceEffectName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ShootEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* TraceEffect;

public:
	AHA_Sniper();

public:

	//Shotgun shoot
	virtual void StartWeaponAction() override;
	virtual void StopWeaponAction() override;

	//Shot display
	void GenerateShot(FVector Offset);
};
