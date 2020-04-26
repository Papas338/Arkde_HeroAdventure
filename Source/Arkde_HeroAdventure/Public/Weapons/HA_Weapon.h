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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float DamageDealt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		TSubclassOf<UDamageType> DamageType;

		ACharacter* CurrentOwner;

public:	
	// Sets default values for this actor's properties
	AHA_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartWeaponAction();
	virtual void StopWeaponAction();

	void CurrentWeaponOwner(ACharacter* WeaponOwner);
};
