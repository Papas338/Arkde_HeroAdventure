// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_LaunchPad.generated.h"

class AHA_Character;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_LaunchPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHA_LaunchPad();

protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* HitboxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* LaunchPadComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* ArrowComponent;
	  
protected:
	//Variables
	UPROPERTY()
		AHA_Character* Player;

	UPROPERTY()
		FVector LaunchDirection;

	UPROPERTY()
		float x;

	UPROPERTY()
		float y;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Elements")
		bool bIsOverlapped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Funtions that can be used on Blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision")
		void BP_Collision();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision")
		void BP_CollisionEnd();

	//This function executes the impulse
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void JumpPadAction();

	//This functions says the direction that the impulse will be executed
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		FVector GetLaunchDirection();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Player detection
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
