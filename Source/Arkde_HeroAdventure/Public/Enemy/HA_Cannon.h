// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_Cannon.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class USceneComponent;
class AHA_Character;
class AHA_Bot;
class USoundCue;
class AHA_GameMode;
class AHA_CannonsTrigger;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Cannon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* CannonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCapsuleComponent* HitBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* ShotLocation;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Cannon")
		bool bIsBotAlived;

	UPROPERTY(BlueprintReadOnly, Category = "Cannon")
		bool bIsCannonActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
		TSubclassOf<AHA_Bot> BotToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
		float CannonAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		USoundCue* ShotSound;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_Character* PlayerReference;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_GameMode* GameModeReference;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_CannonsTrigger* CannonTriggerReference;

	UPROPERTY(BlueprintReadOnly, Category = "Rotation")
		FVector PlayerPosition;

	UPROPERTY(BlueprintReadOnly, Category = "Rotation")
		FRotator PointingDirection;

public:
	// Sets default values for this actor's properties
	AHA_Cannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShootBot();

	void SetIsBotAlived(bool NewValue) { bIsBotAlived = NewValue; };

protected:
	void RotateCannon();

	UFUNCTION()
	void ActivateCannon();

	UFUNCTION()
	void DeactivateCannon(float EnemiesKilled);
};
