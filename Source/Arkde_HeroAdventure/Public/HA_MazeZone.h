// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_MazeZone.generated.h"

class UBoxComponent;
class AHA_GameMode;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_MazeZone : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* HitBoxComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Alert")
		bool bIsInZone;

	UPROPERTY(BlueprintReadOnly, Category = "Alert")
		AHA_GameMode* GameModeReference;
	
public:	
	// Sets default values for this actor's properties
	AHA_MazeZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void EnterZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	bool IsInZone() { return bIsInZone; };
};
