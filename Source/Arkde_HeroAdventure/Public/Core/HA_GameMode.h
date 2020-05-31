// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HA_GameMode.generated.h"

class AHA_Character;
class AHA_SpectatingCamera;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHA_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		AHA_SpectatingCamera* GameOverCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
		float CameraBlendTime;

protected:
	virtual void BeginPlay() override;

	void SetUpSpectatingCameras();
			
public:
	void Victory(AHA_Character* Character);
	void GameOver(AHA_Character* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Victory(AHA_Character* Character);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_GameOver(AHA_Character* Character);

	void ChangeToSpectatorCamera(AHA_Character* Character, AHA_SpectatingCamera* SpectatorCamera);

	void DestroySceneObject(AActor* ThisActor, float TimeToDestroy);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_DestroySceneObject(AActor* ThisActor, float TimeToDestroy);
};
