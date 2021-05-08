// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "HA_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHA_CheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:

	UFUNCTION(exec)
	void HA_UltimateReady();

};
