// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_MainMenuMusic.generated.h"

class UBillboardComponent;
class UAudioComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_MainMenuMusic : public AActor
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* MusicBillboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAudioComponent* MusicAudioComponent;

public:
	// Sets default values for this actor's properties
	AHA_MainMenuMusic();
};