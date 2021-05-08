// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_HUDGameStatus.generated.h"

class AHA_GameMode;

UCLASS()
class ARKDE_HEROADVENTURE_API UHS_HUDGameStatus : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		FName GameStateName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FName VictoryName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		FName GameOverName;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		AHA_GameMode* GameModeReference;
	
public:

	UFUNCTION(BlueprintCallable)
		void InitializeWidget();

	UFUNCTION()
		void OnVictory();

	UFUNCTION()
		void OnGameOver();
};
