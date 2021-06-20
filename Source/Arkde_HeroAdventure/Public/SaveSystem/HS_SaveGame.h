// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HS_SaveGame.generated.h"

/**
 *
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_SaveGame : public USaveGame
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "SaveData")
		bool bAreCannonsActive;

	UPROPERTY(VisibleDefaultsOnly, Category = "SaveData")
		FVector PlayerPosition;

	UPROPERTY(VisibleDefaultsOnly, Category = "SaveData")
		TArray<FName> KeysOwned;

public:
	UFUNCTION(BlueprintCallable)
		void SetAreCannonsActive(bool NewState) { bAreCannonsActive = NewState; };

	UFUNCTION(BlueprintCallable)
		bool GetAreCannonsActive() { return bAreCannonsActive; };

	UFUNCTION(BlueprintCallable)
		void SetPlayerPosition(FVector NewPosition) { PlayerPosition = NewPosition; };

	UFUNCTION(BlueprintCallable)
		FVector GetPlayerPosition() { return PlayerPosition; };

	UFUNCTION(BlueprintCallable)
		void SetKeyToPlayer(FName NewKey) { KeysOwned.Add(NewKey); };

	UFUNCTION(BlueprintCallable)
		TArray<FName> GetPlayerKeys() { return KeysOwned; };

};
