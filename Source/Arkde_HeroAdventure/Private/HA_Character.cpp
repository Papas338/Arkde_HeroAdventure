// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHA_Character::AHA_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm_Component"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_Camera"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AHA_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Player movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AHA_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHA_Character::MoveRight);

	//Execute action
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AHA_Character::ExecutingAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &AHA_Character::StopAction);

	//Player camera
	PlayerInputComponent->BindAxis("LookVertical", this, &AHA_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &ACharacter::AddControllerYawInput);

	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHA_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHA_Character::StopJumping);

	//Evade
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AHA_Character::Evade);
		
}

void AHA_Character::AddControllerPitchInput(float value) {
	Super::AddControllerPitchInput(bIsLookInverted ? value : -value);
}



void AHA_Character::Jump()
{
	Super::Jump();
}

void AHA_Character::StopJumping()
{
	Super::StopJumping();
}

void AHA_Character::MoveForward(float value)
{
	ForwardMovementVector = GetActorForwardVector() * value;
	AddMovementInput(ForwardMovementVector);
	SetPlayerRotation();
}

void AHA_Character::MoveRight(float value)
{
	RightMovementVector = GetActorRightVector() * value;
	AddMovementInput(RightMovementVector);
	SetPlayerRotation();
}

void AHA_Character::Evade()
{
// 	float tempGroundFriction;
// 	tempGroundFriction = GroundFriction;
 	if ((GetActorLocation().Z >= 110) && (GetActorLocation().Z <= 111))
 	{
		LaunchCharacter(MovementDirection * 1000 * ImpulseStrenght, false, false);
	}
	
}

void AHA_Character::SetPlayerRotation()
{
	MovementDirection = (ForwardMovementVector + RightMovementVector) / 2;
 	if (!MovementDirection.IsZero()) {
 		PlayerRotation = MovementDirection.Rotation() + FRotator(0, -90, 0);
 		GetMesh()->SetWorldRotation(PlayerRotation);
 	}
}

void AHA_Character::ExecutingAction()
{
	bIsDoingAction = true;
}

void AHA_Character::StopAction()
{
	bIsDoingAction = false;
}

