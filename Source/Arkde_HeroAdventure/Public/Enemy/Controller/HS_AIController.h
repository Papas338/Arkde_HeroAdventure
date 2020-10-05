// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HS_AIController.generated.h"

class UBehaviorTree;
class AHA_Enemy;
class UBlackboardComponent;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHS_AIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		UBlackboardComponent* MyBlackboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAIPerceptionComponent* AIPerceptionComponent; //Perception Component

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		bool bPlayerStatus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		FName WaitingTimeKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		FName SeeingPlayerKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		FName IsPlayerAliveKeyName;

	AHA_Enemy* MyEnemy;
	
public:
	AHS_AIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateSenses(const TArray<AActor*>& UpdatedActors);

public:
};
