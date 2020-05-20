// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Spear.h"
#include "HA_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AHA_Spear::AHA_Spear()
{
	DamageDealt = 5.0f;
	ComboMultiplier = 1.0;
	MaxComboMultiplier = 5.0f;
	bIsComboAvailable = true;
}

void AHA_Spear::BeginPlay()
{
	Super::BeginPlay();
	AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentOwner);
	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->RightHandSpearComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Spear::DealDamage);
		OwnerCharacter->LeftHandSpearComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Spear::DealDamage);
	}
}

void AHA_Spear::StartWeaponAction()
{
 	if (bisDoingMelee)
	{
 		if (bIsComboAvailable)
 		{
 			if (ComboMultiplier < MaxComboMultiplier)
 			{
 				ComboMultiplier += 0.5;
 				SetComboAvailable(false);
 			}
 			else
 			{
 				return;
 			}
 		}
 		else
 		{
 			return;
 		}
   	}
	
	if (IsValid(CurrentOwner))
	{
		int MontageSelected = FMath::RandRange(0, 1);
		AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentOwner);
		if (IsValid(OwnerCharacter))
		{
			OwnerCharacter->MyAnimInstance->Montage_Play(OwnerCharacter->MeleeMontage[MontageSelected]);
		}		
	}
	SetDoingMelee(true);
}

void AHA_Spear::StopWeaponAction()
{

}

void AHA_Spear::SetDoingMelee(bool NewDoingMeleeStatus)
{
	bisDoingMelee = NewDoingMeleeStatus;
}

void AHA_Spear::SetComboAvailable(bool NewComboAvailableState)
{
	bIsComboAvailable = NewComboAvailableState;
}

void AHA_Spear::ResetCombo()
{
	ComboMultiplier = 1.0f;
	SetComboAvailable(false);
}

void AHA_Spear::DealDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentOwner);
	if (IsValid(OwnerCharacter))
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, DamageDealt * ComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), OwnerCharacter, nullptr);
	}
}
