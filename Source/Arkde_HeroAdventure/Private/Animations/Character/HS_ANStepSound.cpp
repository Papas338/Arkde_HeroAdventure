// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Character/HS_ANStepSound.h"
#include "Components/SkeletalMeshComponent.h"
#include "HA_Character.h"

void UHS_ANStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* PlayerActor = MeshComp->GetOwner();
	if (IsValid(PlayerActor))
	{
		AHA_Character* PlayerCharacter = Cast<AHA_Character>(PlayerActor);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->PlayStepSound();
		}
	}
}