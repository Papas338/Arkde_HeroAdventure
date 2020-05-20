// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HS_ANSpearAttackDone.h"
#include "Components/SkeletalMeshComponent.h"
#include "HA_Character.h"
#include "Weapons/HA_Spear.h"

void UHS_ANSpearAttackDone::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* PlayerActor = MeshComp->GetOwner();
	if (IsValid(PlayerActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(PlayerActor);
		if (IsValid(PlayerCharacter))
		{
			TSubclassOf<AHA_Weapon> SpearWeaponClass = PlayerCharacter->GetSpear();
			AHA_Weapon* SpearWeapon = SpearWeaponClass->GetDefaultObject<AHA_Weapon>();
			if (IsValid(SpearWeapon))
			{
				AHA_Spear* UsableWeapon = Cast<AHA_Spear>(SpearWeapon);
				if (IsValid(UsableWeapon))
				{
					UsableWeapon->SetDoingMelee(false);
				}
			}
		}
	}
}
