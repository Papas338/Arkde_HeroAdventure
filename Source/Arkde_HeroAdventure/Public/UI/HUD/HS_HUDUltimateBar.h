// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_HUDUltimateBar.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_HUDUltimateBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		float UltimatePercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		FLinearColor UltimateColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FLinearColor UltimateColorFull;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FLinearColor UltimateColorEmpty;

public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void UpdateUltimateBar(float CurrentUltimateCharge, float MaxUltimateCharge);

	UFUNCTION()
		void UpdateUltimateStatus(bool bIsUltimateReady);

};
