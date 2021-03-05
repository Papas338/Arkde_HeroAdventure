// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "HA_Character.h"
#include "Components/HA_HealthComponent.h"

void UHS_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			UHA_HealthComponent* PlayerHealthComponent = PlayerCharacter->GetHealthComponent();
				if (IsValid(PlayerHealthComponent))
				{
					PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &UHS_HUDHealthBar::UpdateHealthBar);
				}
		}
	}
}

void UHS_HUDHealthBar::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(HealthColorEmpty, HealthColorFull, HealthPercent);
}
