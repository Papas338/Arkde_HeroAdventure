// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_WeaponSpawner.generated.h"

class USphereComponent;
class UStaticMeshomponent;
class AHA_Character;
class AHA_GameMode;
class AHA_Weapon;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_WeaponSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* WSHitBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* WeaponSpawnerComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AHA_Weapon> WeaponToDisplay;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		AHA_Character* OverlappingPlayer;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		bool bIsPlayerOverlapping;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_GameMode* GameModeReference;
	
public:	
	// Sets default values for this actor's properties
	AHA_WeaponSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void PlayerEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void PlayerExitOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void GiveWeapon();
};
