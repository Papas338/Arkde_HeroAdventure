// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HA_Character.h"
#include "HA_Enemy.generated.h"

class AHA_PathActor;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Enemy : public AHA_Character
{
	GENERATED_BODY()

protected:
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
		AHA_PathActor* MyPath;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void HealthChanged(UHA_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

public:
	AHA_Enemy();

};
