// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_Goal.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Goal : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goal")
	UStaticMeshComponent* GoalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goal")
	USphereComponent* GoalHitBoxComponent;

protected:

	
public:	
	// Sets default values for this actor's properties
	AHA_Goal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void GoalReached();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
