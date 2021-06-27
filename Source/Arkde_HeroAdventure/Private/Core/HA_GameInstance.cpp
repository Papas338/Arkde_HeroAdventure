// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/HS_SaveGame.h"
#include "Core/HA_SpawnPoint.h"

UHA_GameInstance::UHA_GameInstance()
{
	SaveSlotName = "HS_SaveData";
	PlayerPosition = FVector(0.0f, 0.0f, 100.0f);
}

void UHA_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(UHS_SaveGame::StaticClass());
	}
	if (IsValid(SaveGameObject))
	{
		UHS_SaveGame* SaveFile = Cast<UHS_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			SaveFile->SetAreCannonsActive(bAreCannonsActive);
			SaveFile->SetPlayerPosition(PlayerPosition);
			if (!KeysOwned.Num() == 0)
			{
				for (FName KeyToAdd : KeysOwned)
				{
					SaveFile->SetKeyToPlayer(KeyToAdd);
				}
			}			

			UGameplayStatics::SaveGameToSlot(SaveFile,SaveSlotName, 0);
		}
	}
}

void UHA_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else
	{
		ResetData();
	}
	if (IsValid(SaveGameObject))
	{
		UHS_SaveGame* SaveFile = Cast<UHS_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			PlayerPosition = SaveFile->GetPlayerPosition();
			bAreCannonsActive = SaveFile->GetAreCannonsActive();
			KeysOwned = SaveFile->GetPlayerKeys();
		}
	}
}

void UHA_GameInstance::ResetData()
{
	PlayerPosition = FVector(-32.0f, 129.0f, 100.0f);
	bAreCannonsActive = false;
	KeysOwned.Empty();
	BP_ResetData();
}
