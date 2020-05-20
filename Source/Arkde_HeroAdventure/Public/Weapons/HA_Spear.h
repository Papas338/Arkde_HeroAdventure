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
	UPROPERTY(BlueprintReadOnly, Category = "Spear")
		bool bisDoingMelee;

	UPROPERTY(BlueprintReadOnly, Category = "Spear")
		bool bIsComboAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spear")
		float ComboMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spear")
		float MaxComboMultiplier;

public:
	AHA_Spear();

public:
	virtual void BeginPlay() override;
	//Spear attack
	virtual void StartWeaponAction() override;
	virtual void StopWeaponAction() override;

	void SetDoingMelee(bool NewDoingMeleeStatus);
	void SetComboAvailable(bool NewComboAvailableState);
	
	void ResetCombo();

	UFUNCTION()
	void DealDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
