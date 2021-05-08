// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_AmbientMusic.generated.h"

class UBillboardComponent;
class UAudioComponent;
class AHA_GameMode;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_AmbientMusic : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* MusicBillboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* MusicAudioComponent;

protected:

	FName AlertParamName;

	AHA_GameMode* GameModeReference;

public:	
	// Sets default values for this actor's properties
	AHA_AmbientMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void StopLevelMusic();

	UFUNCTION()
		void ChangeLevelMusic(bool bIsAlertMode);
};
