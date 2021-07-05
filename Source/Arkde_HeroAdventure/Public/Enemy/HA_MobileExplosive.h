// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HA_MobileExplosive.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AHA_Character;
class UHA_HealthComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_MobileExplosive : public APawn
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* HitBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHA_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* ExplosiveMesh;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float MinDistanceToTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float ForceMagnitude;

	UPROPERTY(BlueprintReadOnly, Category = "Path")
		FVector NextPathPoint;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_Character* PlayerReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Self Destruct")
		bool bIsExploded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Self Destruct")
		bool bCountdownStarted;

	FTimerHandle TimerHandle_SelfDamage;

public:
	// Sets default values for this pawn's properties
	AHA_MobileExplosive();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void SelfDamage();

	void SelfDestruct();

	FVector GetNextPathPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void DamageTaken(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);
};
