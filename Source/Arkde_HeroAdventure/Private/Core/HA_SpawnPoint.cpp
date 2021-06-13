// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_SpawnPoint.h"
#include "Components/BillboardComponent.h"

// Sets default values
AHA_SpawnPoint::AHA_SpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpawnBillboardComponent"));
}


