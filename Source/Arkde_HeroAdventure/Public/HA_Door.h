// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Door : public AActor
{
	GENERATED_BODY()
		
protected:

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* CustomRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* DoorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* DoorFrameComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* OpenZoneComponent;

protected:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My door")
		bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My door")
		float angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My door")
		FName DoorTag;


public:
	// Sets default values for this actor's properties
	AHA_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Detect player
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//Checks if the player can open the door
	UFUNCTION()
		void CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//Opens the door
	void OpenDoor();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
