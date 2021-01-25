// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/HA_Bot.h"
#include "HA_ExplosiveBot.generated.h"

class AHA_Character;
class AHA_Cannon;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_ExplosiveBot : public AHA_Bot
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Self Destruct")
		bool bIsExploded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Self Destruct")
		bool bCountdownStarted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cannon")
		float ShotStrenght;

	FTimerHandle TimerHandle_SelfDamage;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_Character* PlayerReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ExplosionEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Cannon")
		AHA_Cannon* MyCannon;

public:
	AHA_ExplosiveBot();

protected:
	virtual void BeginPlay() override;

	void SelfDamage();

	void SelfDestruct();

	FVector GetNextPoint();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void DamageTaken(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

	void SetMyCannon(AHA_Cannon* NewCannon) { MyCannon = NewCannon; };
};
