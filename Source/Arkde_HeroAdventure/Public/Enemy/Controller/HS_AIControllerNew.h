// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HS_AIControllerNew.generated.h"

class UBehaviorTree;
class AHA_Enemy;
class UBlackboardComponent;
class UAIPerceptionComponent;
class AHA_GameMode;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHS_AIControllerNew : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		UBlackboardComponent* MyBlackboard;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		FName IsPlayerAliveKeyName;

	UPROPERTY(BlueprintReadWrite, Category = "AI controller")
		bool bReceivingDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI controller")
		FName WaitingTimeKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI controller")
		FName CanSeePlayerKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI controller")
		FName HasReceivedDamageKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI controller")
		FName TargetLocationKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI controller")
		UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(BlueprintReadOnly, Category = "AI controller")
		AHA_Enemy* MyEnemy;

	UPROPERTY(BlueprintReadOnly, Category = "References")
		AHA_GameMode* GameModeReference;

public:

	AHS_AIControllerNew();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateSenses(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
		void NotifyPlayerDeath();

public:
	void SetReceivingDamage(bool bNewState) { bReceivingDamage = bNewState; };

	void DeactivateAIPerception();
};
