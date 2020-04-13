// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHA_Character();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	//Variables
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		bool bIsLookInverted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float ImpulseStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector MovementDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector ForwardMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector RightMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator PlayerRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Physics")
		float defaultGroundFriction;

	UPROPERTY()
		FTimerHandle EvadeFrictionTimer;

	FVector LaunchStrenght;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		bool bIsDoingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		float tempZ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Jump() override;
	virtual void StopJumping() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void Evade();

	void CalculateMovementDirection();

	void SetPlayerRotation();

	void ExecutingAction();
	void StopAction();

	void RestoreFriction();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerPitchInput(float value) override;


};
