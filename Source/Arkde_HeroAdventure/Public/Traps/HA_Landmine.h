// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/HA_Trap.h"
#include "HA_Landmine.generated.h"

class UBoxComponent;
class AHA_GameMode;

/**
 *
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Landmine : public AHA_Trap
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* AreaDetectionComponent;
	//Variables
public:
	AHA_GameMode* GameModeReference;

	AController* thisController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trap")
		float DamageRadius;

public:
	// Sets default values for this actor's properties
	AHA_Landmine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void OnHitReceived(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

	UFUNCTION()
		void DetectionAlarm(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void TrapActive(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
