// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_HUDHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_HUDHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColorFull;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColorEmpty;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

};
