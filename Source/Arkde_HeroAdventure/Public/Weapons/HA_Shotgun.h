// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HA_Weapon.h"
#include "HA_Shotgun.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Shotgun : public AHA_Weapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Linetrace")
		float TraceLenght;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Linetrace")
		bool bDrawLine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ShootEffect;

public:
	AHA_Shotgun();

public:

	virtual void StartWeaponAction() override;
	virtual void StopWeaponAction() override;

	
};
