// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HA_Bot.generated.h"

class AHA_Enemy;
class UStaticMeshComponent;
class USphereComponent;
class UHA_HealthComponent;

UENUM(Blueprintable)
enum class EHA_BotType : uint8
{
	BotType_Player		UMETA(DisplayName = "Ally"),
	BotType_Enemy		UMETA(DisplayName = "Enemy")
};

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
	UPROPERTY(BlueprintReadOnly, Category = "Enemies")
		FVector EnemyLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies")
		TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies")
		TSubclassOf<AActor> BotClass;

	UPROPERTY(BlueprintReadOnly)
		TArray<AActor*> EnemyArray;

	UPROPERTY(BlueprintReadOnly)
		TArray<AActor*> BotArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EHA_BotType BotType;

public:
	// Sets default values for this pawn's properties
	AHA_Bot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FindEnemies();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FVector LowestHealthEnemyPosition();

	UFUNCTION(BlueprintCallable)
		EHA_BotType GetCharacterType() { return BotType; };
};
