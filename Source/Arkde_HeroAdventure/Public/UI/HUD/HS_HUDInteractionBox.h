// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_HUDInteractionBox.generated.h"

class AHA_GameMode;

/**
 *
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_HUDInteractionBox : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		FName InteractionTextName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FName ShowingName;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		AHA_GameMode* GameModeReference;

public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void OnOverlap();

	UFUNCTION()
		void OnStopOverlap();

};
