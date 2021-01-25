// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HA_Bot.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UHA_HealthComponent;
class UMaterialInstanceDynamic;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Bot : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* HitBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHA_HealthComponent* HealthComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Path")
		FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float MinDistanceToTarget;

	UMaterialInstanceDynamic* BotMaterial;

public:
	// Sets default values for this pawn's properties
	AHA_Bot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetNextPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
