// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HS_ANSComboTimeWindow.h"
#include "Components/SkeletalMeshComponent.h"
#include "HA_Character.h"
#include "Weapons/HA_Spear.h"

void UHS_ANSComboTimeWindow::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* ThisActor = MeshComp->GetOwner();
	if (IsValid(ThisActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(ThisActor);
		if (IsValid(PlayerCharacter))
		{
			TSubclassOf<AHA_Weapon> SpearWeaponClass = PlayerCharacter->GetSpear();
			AHA_Weapon* SpearWeapon = SpearWeaponClass->GetDefaultObject<AHA_Weapon>();
			if (IsValid(SpearWeapon))
			{
				AHA_Spear* UsableWeapon = Cast<AHA_Spear>(SpearWeapon);
				if (IsValid(UsableWeapon))
				{
					UsableWeapon->SetComboAvailable(true);
				}
			}
		}
	}
}

void UHS_ANSComboTimeWindow::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* ThisActor = MeshComp->GetOwner();
	if (IsValid(ThisActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(ThisActor);
		if (IsValid(PlayerCharacter))
		{
			TSubclassOf<AHA_Weapon> SpearWeaponClass = PlayerCharacter->GetSpear();
			AHA_Weapon* SpearWeapon = SpearWeaponClass->GetDefaultObject<AHA_Weapon>();
			if (IsValid(SpearWeapon))
			{
				AHA_Spear* UsableWeapon = Cast<AHA_Spear>(SpearWeapon);
				if (IsValid(UsableWeapon))
				{
					UsableWeapon->ResetCombo();
				}
			}
		}
	}
}
