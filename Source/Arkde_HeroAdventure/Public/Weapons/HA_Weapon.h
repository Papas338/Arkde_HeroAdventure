// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_Weapon.generated.h"

class UDamageType;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Weapon : public AActor
{
	GENERATED_BODY()
	
protected:
	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float DamageDealt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		TSubclassOf<UDamageType> DamageType;

		ACharacter* CurrentWeaponOwner;

public:	
	// Sets default values for this actor's properties
	AHA_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Attack functions
	virtual void StartWeaponAction();
	virtual void StopWeaponAction();

	//Finds the owner for the weapon
	void SetWeaponOwner(ACharacter* WeaponOwner);
};
