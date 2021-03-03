// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/HS_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Core/HA_GameInstance.h"



void UHS_MainMenuWidget::NewGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);

	UHA_GameInstance* GameInstanceReference = Cast<UHA_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->ResetData();
	}

	BP_NewGame();
}

void UHS_MainMenuWidget::Continue()
{
	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);

	UHA_GameInstance* GameInstanceReference = Cast<UHA_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->LoadData();
	}

	BP_Continue();
}

void UHS_MainMenuWidget::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);

	BP_QuitGame();
}
