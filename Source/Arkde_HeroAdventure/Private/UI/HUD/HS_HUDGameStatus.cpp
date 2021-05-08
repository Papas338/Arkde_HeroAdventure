// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDGameStatus.h"
#include "Core/HA_GameMode.h"

void UHS_HUDGameStatus::InitializeWidget()
{
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &UHS_HUDGameStatus::OnVictory);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &UHS_HUDGameStatus::OnGameOver);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UHS_HUDGameStatus::OnVictory()
{
	GameStateName = VictoryName;
	SetVisibility(ESlateVisibility::Visible);
}

void UHS_HUDGameStatus::OnGameOver()
{
	GameStateName = GameOverName;
	SetVisibility(ESlateVisibility::Visible);
}
