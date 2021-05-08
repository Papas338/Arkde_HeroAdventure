// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HS_HUDObjective.h"

void UHS_HUDObjective::ObjectiveCompleted()
{
	bIsCompleted = true;
	CurrentColor = CompletedColor;
}
