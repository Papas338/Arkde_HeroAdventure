// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_EnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		float HealthPercent;

public:

	UFUNCTION()
		void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	
};
