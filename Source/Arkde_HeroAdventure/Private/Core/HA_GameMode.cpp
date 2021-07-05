// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_GameMode.h"
#include "HA_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "HA_SpectatingCamera.h"
#include "Kismet/GameplayStatics.h"
#include "HA_SpectatingCamera.h"
#include "Sound/SoundCue.h"
#include "HA_MazeZone.h"

AHA_GameMode::AHA_GameMode()
{
	MapName = "MainMenu";
}

void AHA_GameMode::BeginPlay()
{
	Super::BeginPlay();

	SetUpSpectatingCameras();

	AActor* MazeActor = UGameplayStatics::GetActorOfClass(GetWorld(), AHA_MazeZone::StaticClass());
	if (IsValid(MazeActor))
	{
		MazeLevel = Cast<AHA_MazeZone>(MazeActor);
	}
}

/*The following functions control camera behaviour
* 
* - SetUpSpectatingCameras()
* - ChangeToSpectatorCamera()
*/
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

void AHA_GameMode::ChangeToSpectatorCamera(AHA_Character* Character, AHA_SpectatingCamera* SpectatorCamera)
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

/*The following functions control core funcions in the game
* 
* - BackToMainMenu()
* - PlayMusic()
* - Victory()
* - GameOver()
* - CheckAlerts()
* - DestroySceneObject()
*/
void AHA_GameMode::BackToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName);
}

void AHA_GameMode::PlayMusic(USoundCue* GameMusic)
{
	if (!IsValid(GameMusic))
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), GameMusic);
}

void AHA_GameMode::Victory(AHA_Character* Character)
{
	ChangeToSpectatorCamera(Character, VictoryCamera);
	Character->DisableInput(nullptr);

	OnVictoryDelegate.Broadcast();

	PlayMusic(VictoryMusic);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &AHA_GameMode::BackToMainMenu, 5.0f, false);

	BP_Victory(Character);
}

void AHA_GameMode::GameOver(AHA_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
		
	ChangeToSpectatorCamera(Character, GameOverCamera);
	Character->DisableInput(nullptr);

	OnGameOverDelegate.Broadcast();

	PlayMusic(GameOverMusic);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &AHA_GameMode::BackToMainMenu, 8.0f, false);
	
	BP_GameOver(Character);
}

void AHA_GameMode::CheckAlerts()
{
	bIsInMaze = false;

	if (IsValid(MazeLevel)) {
		if (MazeLevel->IsInZone())
		{
			bIsInMaze = true;
		}
		else
		{
			bIsInMaze = false;
		}
	}
	OnMapZoneChangeDelegate.Broadcast(bIsInMaze);

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

/*The following functions control actions done by the player and its interaction with the world
* 
* - AddKeyToCharacter()
* - AddEnemyKilled()
* - PickUpOverlap()
*/
void AHA_GameMode::AddKeyToCharacter(AHA_Character* KeyOwner, FName KeyTag)
{
	if (IsValid(KeyOwner))
	{
		KeyOwner->AddKey(KeyTag);
	}
}

void AHA_GameMode::AddEnemyKilled()
{
	EnemiesKilled++;
	OnEnemyKilledDelegate.Broadcast(EnemiesKilled);
}

void AHA_GameMode::PickUpOverlap(bool bIsOverlapping)
{
	if (bIsOverlapping) {
		OnPlayerOverlapDelegate.Broadcast();
	}
	else
	{
		OnPlayerExitOverlapDelegate.Broadcast();
	}
}

