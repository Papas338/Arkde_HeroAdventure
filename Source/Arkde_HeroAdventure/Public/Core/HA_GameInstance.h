// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HA_GameInstance.generated.h"

class AHA_SpawnPoint;

UCLASS()
class ARKDE_HEROADVENTURE_API UHA_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UHA_GameInstance();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
		bool bAreCannonsActive;

	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
		FVector PlayerPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveSystem")
		FString SaveSlotName;

public:

	UFUNCTION(BlueprintCallable)
		void SaveData();

	UFUNCTION(BlueprintCallable)
		void LoadData();

	UFUNCTION(BlueprintCallable)
		void ResetData();

	void SetAreCannonsActive(bool NewState) { bAreCannonsActive = NewState; };

	bool GetAreCannonsActive() { return bAreCannonsActive; };

	void SetPlayerPosition(FVector NewPosition) { PlayerPosition = NewPosition; };

	FVector GetPlayerPosition() { return PlayerPosition; };

protected:

	UFUNCTION(BlueprintImplementableEvent)
		void BP_SaveData();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_LoadData();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_ResetData();

};
