// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/HA_PickUp.h"
#include "HA_Key.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API AHA_Key : public AHA_PickUp
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* KeyMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
		FName Keytag;

public:
	// Sets default values for this actor's properties
	AHA_Key();

public:

	//Returns the tag for the specified key on the scene
	UFUNCTION(BlueprintCallable, Category = "Getter")
		FName GetKeyTag() const { return Keytag; };

protected:

	virtual void PickUpItem(AHA_Character* PickupActor) override;
};
