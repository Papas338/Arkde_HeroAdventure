// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_GameMode.h"
#include "HA_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HA_SpectatingCamera.h"
#include "Kismet/GameplayStatics.h"
#include "HA_SpectatingCamera.h"

void AHA_GameMode::BeginPlay()
{
	Super::BeginPlay();

	SetUpSpectatingCameras();
}

void AHA_GameMode::SetUpSpectatingCameras()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHA_SpectatingCamera::StaticClass(), CameraActors);

	if (CameraActors.Num() > 0)
	{
		for (AActor* SpectatorCameraActor : CameraActors)
		{
			AHA_SpectatingCamera* SpectatingCamera = Cast<AHA_SpectatingCamera>(SpectatorCameraActor);
			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case EHA_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;
				case EHA_SpectatingCameraType::CameraType_Gameover:
					GameOverCamera = SpectatingCamera;
					break;
				default:
					break;
				}
			}
		}
	}
}

void AHA_GameMode::Victory(AHA_Character* Character)
{
	ChangeToSpectatorCamera(Character, VictoryCamera);
	Character->DisableInput(nullptr);

	BP_Victory(Character);
}

void AHA_GameMode::GameOver(AHA_Character* Character)
{
	UE_LOG(LogTemp, Log, TEXT("Funciona"))
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Character->HasToDestroy())
	{
		Character->SetLifeSpan(5.0f);
		Character->DetachFromControllerPendingDestroy();
	}
	else
	{
		ChangeToSpectatorCamera(Character, GameOverCamera);
		Character->DisableInput(nullptr);
	}
	BP_GameOver(Character);
}

void AHA_GameMode::ChangeToSpectatorCamera(AHA_Character * Character, AHA_SpectatingCamera* SpectatorCamera)
{
	if (!IsValid(Character) || !IsValid(SpectatorCamera))
	{
		return;
	}
	AController* ActorController = Character->GetController();
	if (IsValid(ActorController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(ActorController);
		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatorCamera, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void AHA_GameMode::DestroySceneObject(AActor* ThisActor, float TimeToDestroy)
{
	if (!IsValid(ThisActor))
	{
		return;
	}

	ThisActor->SetLifeSpan(TimeToDestroy);

	BP_DestroySceneObject(ThisActor, TimeToDestroy);
}
