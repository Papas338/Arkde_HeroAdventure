// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_SpawnPoint.generated.h"

class UBillboardComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_SpawnPoint : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBillboardComponent* SpawnBillboardComponent;
	
public:	
	// Sets default values for this actor's properties
	AHA_SpawnPoint();

};
