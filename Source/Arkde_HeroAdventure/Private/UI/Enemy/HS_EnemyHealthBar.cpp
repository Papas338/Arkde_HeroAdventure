// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/HS_EnemyHealthBar.h"

void UHS_EnemyHealthBar::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
}
