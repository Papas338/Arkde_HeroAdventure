// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HA_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UHA_HealthComponent*, HealthComponent, AActor *, DamagedActor, float, Damage, const UDamageType *, DamageType, AController *, InstigatedBy, AActor *, DamageCauser);

UCLASS( ClassGroup=(PEACE), meta=(BlueprintSpawnableComponent) )
class ARKDE_HEROADVENTURE_API UHA_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHA_HealthComponent();

protected:
	UPROPERTY(EditAnywhere, Category = "Health Component")
		bool bDebug;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
		bool bIsDead;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Component", meta = (ClampMin = 0.0, UIMin = 0.0))
		float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	AActor* MyOwner;

public:
	UPROPERTY(BlueprintAssignable)
		FOnHealthChangeSignature OnHealthChangeDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	bool IsDead() const { return bIsDead; };

	float GetCurrentHealth() { return CurrentHealth; };
};
