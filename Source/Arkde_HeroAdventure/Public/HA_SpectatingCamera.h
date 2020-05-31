// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM(Blueprintable)
enum class EHA_SpectatingCameraType : uint8
{
	CameraType_None		UMETA(DisplayName = "None"),
	CameraType_Victory	UMETA(DisplayName = "Victory"),
	CameraType_Gameover	UMETA(DisplayName = "GameOver")
};

UCLASS()
class ARKDE_HEROADVENTURE_API AHA_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* CameraMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpectatingCamera")
		EHA_SpectatingCameraType CameraType;

public:	
	// Sets default values for this actor's properties
	AHA_SpectatingCamera();


	EHA_SpectatingCameraType GetCameraType() { return CameraType; };

};
