// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDUltimateBar.h"
#include "Kismet/GameplayStatics.h"
#include "HA_Character.h"

void UHS_HUDUltimateBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->OnUltimateUpdateDelegate.AddDynamic(this, &UHS_HUDUltimateBar::UpdateUltimateBar);
			PlayerCharacter->OnUltimateReadyDelegate.AddDynamic(this, &UHS_HUDUltimateBar::UpdateUltimateStatus);
		}			
	}
}

void UHS_HUDUltimateBar::UpdateUltimateBar(float CurrentUltimateCharge, float MaxUltimateCharge)
{
	UltimatePercent = CurrentUltimateCharge / MaxUltimateCharge;
	UE_LOG(LogTemp, Warning, TEXT("Ultimate: %f"),UltimatePercent)
}

void UHS_HUDUltimateBar::UpdateUltimateStatus(bool bIsUltimateReady)
{
	UltimateColor = bIsUltimateReady ? UltimateColorFull : UltimateColorEmpty;
}
