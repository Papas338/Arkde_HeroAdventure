// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AHA_Weapon;
class UAnimMontage;
class UAnimInstance;
class UCapsuleComponent;
class UHA_HealthComponent;
class AHA_GameMode;
class UHA_UltimateAbilityComponent;
class UHA_GameInstance;

UENUM(Blueprintable)
enum class EHA_CharacterType : uint8
{
	CharacterType_Player	UMETA(DisplayName = "Player"),
	CharacterType_Enemy		UMETA(DisplayName = "Enemy")
};

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHA_Character();

	//Components

	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	//Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCapsuleComponent* RightHandSpearComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCapsuleComponent* LeftHandSpearComponent;

	//Gameplay
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHA_HealthComponent* HealthComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		//UHA_UltimateAbilityComponent* UltimateAbilityComponent;

	//Variables
protected:
	//Player variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic elements")
		EHA_CharacterType CharacterType;

	//Player Basic Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
		bool bIsLookInverted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float walkSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector MovementDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector ForwardMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector RightMovementVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator PlayerRotation;

	//Abilities
	//Evade
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Evade")
		float ImpulseStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Physics|Evade")
		float defaultGroundFriction;

	UPROPERTY(BlueprintReadOnly, Category = "Timers|Evade")
		FTimerHandle EvadeFrictionTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers|Evade")
		FTimerHandle EvadeCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Evade")
		FVector LaunchStrenght;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Evade")
		bool bIsEvadeAvailable;

	//Ultimate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate", meta = (ClampMin = 0.0, UIMin = 0.0))
		float MaxUltimateCharge;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		float CurrentUltimateCharge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Timer", meta = (ClampMin = 0.0, UIMin = 0.0))
		float MaxUltimateDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Timer")
		float CurrentUltimateDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		bool bCanUseUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		bool bIsUsingUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Timer")
		float UltimateDurationFrecuency;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		float NormalSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
		FVector PlayerVelocity;

	FTimerHandle TimerHandle_Ultimate;
	FTimerHandle TimerHandle_CannonShot;

	//Pickups
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
		TArray<FName> KeyTags;

	//Weapons
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		FName RightHandSocket;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		FName LeftHandSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Levels")
		FName MainMenuMapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		AHA_Weapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		AHA_Weapon* AlternativeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		AHA_Weapon* UltimateWeapon;

	UPROPERTY()
		AHA_Weapon* Temp;

	UPROPERTY(BlueprintReadOnly, Category = "Spear")
		bool bisDoingMelee;

	UPROPERTY(BlueprintReadOnly, Category = "Spear")
		bool bIsComboAvailable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spear")
		float ComboMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spear")
		float MaxComboMultiplier;

	int AttackSelected;

	//Gameplay
	AHA_GameMode* GameModeReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Over")
		bool bHasToDestroy;

public:

	//Player Basic Movement
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator tempRotation;

	//Player Basic Gameplay
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bIsDoingAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		bool bIsAiming;

	//Animations
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		TArray<UAnimMontage*> MeleeMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* UltimateMontage;

	UAnimInstance* MyAnimInstance;

	//Weapons

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AHA_Weapon> MeleeWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AHA_Weapon> FireWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AHA_Weapon> UltimateWeaponClass;

	UHA_GameInstance* GameInstanceReference;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Initialize
	void InitializeVariables();
	void InitializeReferences();
	void SetInitialPosition();

	//Jump
	virtual void Jump() override;
	virtual void StopJumping() override;

	//Movement
	void MoveForward(float value);
	void MoveRight(float value);

	void CalculateMovementDirection();
	void SetPlayerRotation();

	//Evade
	void Evade();
	void CooldownFinishedEvade();
	void RestoreFriction();
	
	//Action
	void ExecutingAction();
	void StopAction();
	
	//Aiming
	void Aiming();
	void StopAiming();

	//Attack
	UFUNCTION(BlueprintCallable)
	void StartAttack();
	void StopAttack();

	//Weapons
	void SetInitialWeapon();
	void SetSecondaryWeapon();
	void SetUltimateWeapon();

	//Ultimate Ability
	void UpdateUltimateCharge(float Value);
	void StartUltimate();
	void StopUltimate();
	void UpdateUltimateDuration();
	void UltimateBehaviour();
	void RestorePlayer();
	void RestoreMovement();
	void ShootCannon();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UpdateUltimateDuration();
	
	void ExitToMainMenu();

	//Stats
	UFUNCTION()
	void OnHealthChange(UHA_HealthComponent* ThisHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Character
	UFUNCTION(BlueprintCallable)
	EHA_CharacterType GetCharacterType() { return CharacterType; };

	//Input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	virtual void AddControllerPitchInput(float value) override;

	//Pickups
	void AddKey(FName NewKey);
	bool HasKey(FName Keytag);

	//Gameplay
	virtual FVector GetPawnViewLocation() const override;

	bool HasToDestroy() { return bHasToDestroy; };

	//Weapons
	void SetDoingMelee(bool NewDoingMeleeStatus);

	float GetComboMultiplier() { return ComboMultiplier; };
	void SetComboAvailable(bool NewComboAvailableState);

	void ResetCombo();

	int GetAttackSelected() { return AttackSelected; };
};
