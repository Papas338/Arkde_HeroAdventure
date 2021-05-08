// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDObjectivesContainer.h"
#include "Core/HA_GameMode.h"
#include "UI/HUD/HS_HUDObjective.h"

void UHS_HUDObjectivesContainer::InitializeWidget()
{
	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference)) 
	{
		GameModeReference->OnKeyAddedDelegate.AddDynamic(this, &UHS_HUDObjectivesContainer::UpdateObjectives);
	}
}

void UHS_HUDObjectivesContainer::InitializeObjectives(TArray<UHS_HUDObjective*> NewObjectives)
{
	for (UHS_HUDObjective* NewObjective : NewObjectives) 
	{
		Objectives.AddUnique(NewObjective);
	}
}

void UHS_HUDObjectivesContainer::UpdateObjectives(FName KeyTag)
{
	int ObjectivesIndex = -1;

	if (KeyTag == "KeyA")
	{
		ObjectivesIndex = 0;
	}

	if (KeyTag == "KeyB")
	{
		ObjectivesIndex = 1;
	}

	if (Objectives.IsValidIndex(ObjectivesIndex))
	{
		UHS_HUDObjective* CurrentObjective = Objectives[ObjectivesIndex];
		if (IsValid(CurrentObjective))
		{
			CurrentObjective->ObjectiveCompleted();
		}
	}
}
