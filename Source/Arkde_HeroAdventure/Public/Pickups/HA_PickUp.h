// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_PickUp.generated.h"

class USphereComponent;
class AHA_Character;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_PickUp : public AActor
{
	GENERATED_BODY()

protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* HitBoxComponent;
	
public:	
	// Sets default values for this actor's properties
	AHA_PickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//executes different functions once the player has picked up one of the possible items
	virtual void PickUpItem(AHA_Character* PickupActor);

	//this one can be called from blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
		void BP_PickUp(AHA_Character* PickupActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Detects the player
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
