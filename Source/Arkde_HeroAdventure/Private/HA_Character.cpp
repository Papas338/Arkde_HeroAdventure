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

	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AHA_Character::Aiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AHA_Character::StopAiming);

	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHA_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHA_Character::StopJumping);

	//Evade
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AHA_Character::Evade);
		
	//Gunplay
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHA_Character::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AHA_Character::StopAttack);
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
	bIsEvadeAvailable = true;
}

void AHA_Character::CalculateMovementDirection()
{
	MovementDirection = (ForwardMovementVector + RightMovementVector) / 2;
}

void AHA_Character::SetPlayerRotation()
{
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

void AHA_Character::ExecutingAction()
{
	bIsDoingAction = true;
}

void AHA_Character::StopAction()
{
	bIsDoingAction = false;
}

void AHA_Character::RestoreFriction()
{
	GetCharacterMovement()->GroundFriction = defaultGroundFriction;
}

void AHA_Character::Aiming()
{
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

void AHA_Character::StartAttack()
{
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
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AHA_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		CurrentWeapon->CurrentWeaponOwner(this);
	}
}

void AHA_Character::AddKey(FName NewKey)
{
	KeyTags.Add(NewKey);
}

bool AHA_Character::HasKey(FName Keytag)
{
	return KeyTags.Contains(Keytag);
}


