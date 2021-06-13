// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HS_HUDObjectivesContainer.generated.h"

class AHA_GameMode;
class UHS_HUDObjective;

UCLASS()
class ARKDE_HEROADVENTURE_API UHS_HUDObjectivesContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		AHA_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		TArray<UHS_HUDObjective*> Objectives;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION(BlueprintCallable)
	void InitializeObjectives(TArray<UHS_HUDObjective*> NewObjectives);

	UFUNCTION()
	void UpdateObjectives(float EnemiesKilled);
};
