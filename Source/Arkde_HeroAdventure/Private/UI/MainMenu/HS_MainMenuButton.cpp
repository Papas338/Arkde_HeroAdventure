// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/HS_MainMenuButton.h"

UHS_MainMenuButton::UHS_MainMenuButton()
{
	CheckFocusRate = 0.1f;
}

void UHS_MainMenuButton::Start()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckFocus, this, &UHS_MainMenuButton::CheckFocus, CheckFocusRate, true);
}

void UHS_MainMenuButton::CheckFocus()
{
	if (IsHovered())
	{
		//There's a mouse
		SetKeyboardFocus();
		SetButtonStyle(EHA_ButtonStyleType::ButtonStyleType_Mouse);
	}
	else
	{
		EHA_ButtonStyleType StyleTypeSelected = HasKeyboardFocus() ? EHA_ButtonStyleType::ButtonStyleType_KeySelected : EHA_ButtonStyleType::ButtonStyleType_KeyNoSelected;
		SetButtonStyle(StyleTypeSelected);
	}
}

void UHS_MainMenuButton::SetButtonStyle(EHA_ButtonStyleType NewStyleType)
{
	BP_SetButtonStyle(NewStyleType);
}
