// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Spear.h"
#include "HA_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AHA_Spear::AHA_Spear()
{

}

void AHA_Spear::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(CurrentWeaponOwner))
	{
		AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentWeaponOwner);
			if (IsValid(OwnerCharacter))
			{
				OwnerCharacter->RightHandSpearComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Spear::DealDamage);
				OwnerCharacter->LeftHandSpearComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_Spear::DealDamage);
			}
	}
}

void AHA_Spear::StartWeaponAction()
{
	if (IsValid(CurrentWeaponOwner))
	{
		AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentWeaponOwner);
		if (IsValid(OwnerCharacter))
		{
			OwnerCharacter->MyAnimInstance->Montage_Play(OwnerCharacter->MeleeMontage[OwnerCharacter->GetAttackSelected()]);
			OwnerCharacter->SetDoingMelee(true);
		}
	}
}

void AHA_Spear::StopWeaponAction()
{

}

void AHA_Spear::DealDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(CurrentWeaponOwner))
	{
		AHA_Character* OwnerCharacter = Cast<AHA_Character>(CurrentWeaponOwner);
		if (IsValid(OwnerCharacter))
		{
			UGameplayStatics::ApplyPointDamage(OtherActor, DamageDealt * OwnerCharacter->GetComboMultiplier(), SweepResult.Location, SweepResult, GetInstigatorController(), OwnerCharacter, nullptr);
		}
	}
}
