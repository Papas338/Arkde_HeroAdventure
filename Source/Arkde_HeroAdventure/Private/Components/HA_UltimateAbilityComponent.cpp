// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HA_UltimateAbilityComponent.h"

// Sets default values for this component's properties
UHA_UltimateAbilityComponent::UHA_UltimateAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxUltimateCharge = 10.0f;
}


// Called when the game starts
void UHA_UltimateAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentUltimateCharge = MaxUltimateCharge;
	
}


// Called every frame
void UHA_UltimateAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateUltimateValue(DeltaTime);
}

void UHA_UltimateAbilityComponent::UpdateUltimateValue(float Value)
{
	CurrentUltimateCharge = FMath::Clamp(CurrentUltimateCharge - Value, 0.0f, MaxUltimateCharge);

}

