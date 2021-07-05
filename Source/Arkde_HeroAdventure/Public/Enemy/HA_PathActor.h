// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_PathActor.generated.h"

class UBillboardComponent;

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_PathActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* PathComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path", meta = (MakeEditWidget = true))
	TArray<FVector> PathPoints;

public:	
	// Sets default values for this actor's properties
	AHA_PathActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
