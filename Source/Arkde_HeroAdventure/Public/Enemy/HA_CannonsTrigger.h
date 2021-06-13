// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_CannonsTrigger.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCannonCollisionSignature);

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_CannonsTrigger : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* HitBoxComponent;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCannonCollisionSignature OnCannonCollisionDelegate;
	
public:	
	// Sets default values for this actor's properties
	AHA_CannonsTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void ActiveCannons(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
