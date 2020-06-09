// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HA_Weapon.h"
#include "HA_UltimateCannon.generated.h"

class AHA_Missile;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_UltimateCannon : public AHA_Weapon
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate Launcher")
		FName UltimateSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate Launcher")
		TSubclassOf<AHA_Missile> MissileClass;

	
public:
	AHA_UltimateCannon();

public:
	//Attack functions
	virtual void StartWeaponAction() override;
	virtual void StopWeaponAction() override;
};
