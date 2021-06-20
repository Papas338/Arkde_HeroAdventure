// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDInteractionBox.h"
#include "Core/HA_GameMode.h"

void UHS_HUDInteractionBox::InitializeWidget()
{
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnPlayerOverlapDelegate.AddDynamic(this, &UHS_HUDInteractionBox::OnOverlap);
		GameModeReference->OnPlayerExitOverlapDelegate.AddDynamic(this, &UHS_HUDInteractionBox::OnStopOverlap);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UHS_HUDInteractionBox::OnOverlap()
{
	InteractionTextName = ShowingName;
	SetVisibility(ESlateVisibility::Visible);
}

void UHS_HUDInteractionBox::OnStopOverlap()
{
	SetVisibility(ESlateVisibility::Hidden);
}
