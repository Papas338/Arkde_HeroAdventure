// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HA_Weapon.h"
#include "HA_Spear.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Spear : public AHA_Weapon
{
	GENERATED_BODY()

protected:
// Variables
	
public:
	AHA_Spear();

public:
	virtual void BeginPlay() override;
	//Spear attack
	virtual void StartWeaponAction() override;
	virtual void StopWeaponAction() override;

	UFUNCTION()
	void DealDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
