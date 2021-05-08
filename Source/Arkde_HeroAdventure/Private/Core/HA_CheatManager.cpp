// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_CheatManager.h"
#include "HA_Character.h"
#include "Kismet/GameplayStatics.h"

void UHA_CheatManager::HA_UltimateReady() 
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->UpdateUltimateCharge(10000);
		}
	}
}