// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_Trap.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UHA_HealthComponent;
class UParticleSystem;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Trap : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* HitBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* TrapMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHA_HealthComponent* HealthComponent;

//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap")
		float TrapDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* TrapEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		TSubclassOf<UDamageType> TrapDamageType;

public:
	// Sets default values for this actor's properties
	AHA_Trap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void TrapActive(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
