// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_Character.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Weapons/HA_Weapon.h"

// Sets default values
AHA_Character::AHA_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	//Components initialization
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
	defaultGroundFriction = GetCharacterMovement()->GroundFriction;
	bIsEvadeAvailable = true;
	walkSpeed = 1.0f;

	SetInitialWeapon();
}

// Called every frame
void AHA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
Input

Functions on this section are related with how the game receives player's input

This function changes where the camera turns depending in if it's inverted o no:
- SetupPlayerInputComponent()
- AddControllerPitchInput(value) - This functions takes in the value from the input and inverts it if necessary
*/
void AHA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Player movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AHA_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHA_Character::MoveRight);

	//Player camera
	PlayerInputComponent->BindAxis("LookVertical", this, &AHA_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AHA_Character::Aiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AHA_Character::StopAiming);

	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHA_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHA_Character::StopJumping);

	//Execute action
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AHA_Character::ExecutingAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &AHA_Character::StopAction);
	
	//Evade
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AHA_Character::Evade);
		
	//Weapon gameplay
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHA_Character::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AHA_Character::StopAttack);
}

void AHA_Character::AddControllerPitchInput(float value) {
	Super::AddControllerPitchInput(bIsLookInverted ? value : -value);
}

/*
Movement

The functions on this section are in charge of control the player behavior
On this section we can find the next functions:

In charge of jumping:
- Jump()
- StopJumping()

In charge of moving the player on the scene:
- MoveForward(value) - This functions takes in the value from the input
- MoveRight(value) - This functions takes in the value from the input
- CalculateMovementDirection()
- SetPlayerRotation()
*/
//Jumping
void AHA_Character::Jump()
{
	Super::Jump();
}

void AHA_Character::StopJumping()
{
	Super::StopJumping();
}

//Movement
void AHA_Character::MoveForward(float value)
{
	ForwardMovementVector = GetActorForwardVector() * value * walkSpeed;
	AddMovementInput(ForwardMovementVector);
	SetPlayerRotation();
}

void AHA_Character::MoveRight(float value)
{
	RightMovementVector = GetActorRightVector() * value * walkSpeed;
	AddMovementInput(RightMovementVector);
	SetPlayerRotation();
}

void AHA_Character::CalculateMovementDirection()
{
	//This function finds the vector where the player is moving towards.
	MovementDirection = (ForwardMovementVector + RightMovementVector) / 2;
}

void AHA_Character::SetPlayerRotation()
{
	//Since movement and camera are not linked this function allows the player to face the direction
	//They are walking towards unless it's aiming
	if (bIsAiming)
	{
		return;
	}
	CalculateMovementDirection();
	if (!MovementDirection.IsZero()) {
		PlayerRotation = MovementDirection.Rotation() + FRotator(0, -90, 0);
		GetMesh()->SetRelativeRotation(PlayerRotation);
	}
}

/*
Gameplay

This section is in charge of specific gameplay functions:

General actions:
- ExecutingAction()
- StopAction()

Evade:
- Evade()
- CooldownFinishedEvade()
- RestoreFriction()

Attacking:
- Aiming()
- StopAiming()
- GetPawnViewLocation()
- StartAttack()
- StopAttack()
- SetInitialWeapon()
*/

//General actions
void AHA_Character::ExecutingAction()
{
	//This function indicates that the player is pressing the button to interact with an object
	bIsDoingAction = true;
}

void AHA_Character::StopAction()
{
	bIsDoingAction = false;
}

//Evade
void AHA_Character::Evade()
{
	if ((bIsEvadeAvailable) && (!bIsAiming))
	{
		CalculateMovementDirection();
		GetCharacterMovement()->GroundFriction = 0;
		if ((GetCharacterMovement()->GroundFriction == 0) && (!GetCharacterMovement()->IsFalling())) {
			LaunchStrenght = MovementDirection * ImpulseStrenght * 1000;
			LaunchCharacter(LaunchStrenght, false, false);
			bIsEvadeAvailable = false;
		}
		GetWorld()->GetTimerManager().SetTimer(EvadeFrictionTimer, this, &AHA_Character::RestoreFriction, 1.5f, false);
		GetWorld()->GetTimerManager().SetTimer(EvadeCooldown, this, &AHA_Character::CooldownFinishedEvade, 1, false);
	}
}

void AHA_Character::CooldownFinishedEvade()
{
	//Makes the ability available after the cooldown has finished
	bIsEvadeAvailable = true;
}

void AHA_Character::RestoreFriction()
{
	//Restores the friction to its original value
	GetCharacterMovement()->GroundFriction = defaultGroundFriction;
}

//Attacking
void AHA_Character::Aiming()
{
	//This function switches the character behavior to fit the attitude of holding a gun
	//Rotation
	tempRotation = GetMesh()->GetRelativeRotation();
	bIsAiming = true;
	GetMesh()->SetUsingAbsoluteRotation(false);
	GetMesh()->SetRelativeRotation(SpringArmComponent->GetRelativeRotation() + FRotator(0, -90, 0));

	//Camera
	SpringArmComponent->TargetArmLength = 150;
	SpringArmComponent->SocketOffset.Y = 70;
	SpringArmComponent->SocketOffset.Z = 20;

	//Movement
	walkSpeed = 0.5f;
}

void AHA_Character::StopAiming()
{
	//This function resets the character to its default position
	//Rotation
	bIsAiming = false;
	GetMesh()->SetUsingAbsoluteRotation(true);
	GetMesh()->SetRelativeRotation(tempRotation);

	//Camera
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->SocketOffset.Y = 0;
	SpringArmComponent->SocketOffset.Z = 0;

	//Movement
	walkSpeed = 1.0f;
}

FVector AHA_Character::GetPawnViewLocation() const
{
	//Returns the middle point in the screen
	if (IsValid(TPSCameraComponent))
	{
		return TPSCameraComponent->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void AHA_Character::StartAttack()
{
	//Executes the attack of the selected weapon
	if (IsValid(CurrentWeapon))
	{
		if (bIsAiming)
		{
			CurrentWeapon->StartWeaponAction();
		}
	}
}

void AHA_Character::StopAttack()
{
	if (IsValid(CurrentWeapon))
	{
		if (bIsAiming)
		{
			CurrentWeapon->StopWeaponAction();
		}
	}
}

void AHA_Character::SetInitialWeapon()
{
	//Sets the starter weapon that the player will use 
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AHA_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		CurrentWeapon->CurrentWeaponOwner(this);
	}
}

/*
Interactions

This section contains everything related with the world the player is in

- AddKey(NewKey) - this function adds a new key to the player to hold
- HasKey(Keytag) - this function receives the name from the Keytag the game wants to know if the player has it or not
*/

void AHA_Character::AddKey(FName NewKey)
{
	//Adds the tag from a key to the character so the game can know that the player has picked it up
	KeyTags.Add(NewKey);
}

bool AHA_Character::HasKey(FName Keytag)
{
	//Checks wether the player has an specific key or not
	return KeyTags.Contains(Keytag);
}




