// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HA_Character.h"
#include "HA_Enemy.generated.h"

class AHA_PathActor;
class UCameraComponent;
class UBlackboardComponent;
class AHS_AIControllerNew;
class AHA_KeySpawner;
class UWidgetComponent;
class UHS_EnemyHealthBar;
class AHA_GameMode;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Enemy : public AHA_Character
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* WidgetHealthBarComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		AHS_AIControllerNew* MyController;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		UHS_EnemyHealthBar* EnemyHealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "KeySpawner")
		AHA_KeySpawner* ConnectedSpawner;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		bool bIsSetToDespawn;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
		AHA_PathActor* MyPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
		float waitingTimeOnPathPoint;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		bool bIsAlerted;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		bool bIsShowingHealthBar;

	FTimerHandle TimerHandle_HideHealthBar;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void HealthChanged(UHA_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);

public:
	AHA_Enemy();

	float GetWaitingTime() { return waitingTimeOnPathPoint; };

	bool IsAlerted() { return bIsAlerted; };

	void SetAlerted(bool bValue);

	void SetKeySpawner(AHA_KeySpawner* MySpawner) { ConnectedSpawner = MySpawner; };

protected:

	void ShowHealthBar();

	void HideHealthBar();

};
