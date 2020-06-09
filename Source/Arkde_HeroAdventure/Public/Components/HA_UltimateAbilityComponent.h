// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HA_UltimateAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARKDE_HEROADVENTURE_API UHA_UltimateAbilityComponent : public UActorComponent
{

	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate", meta = (ClampMin = 0.0, UIMin = 0.0))
		float MaxUltimateCharge;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		float CurrentUltimateCharge;


public:	
	// Sets default values for this component's properties
	UHA_UltimateAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateUltimateValue(float Value);

};
