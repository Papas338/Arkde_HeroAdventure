// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_PathActor.h"
#include "Components/BillboardComponent.h"

// Sets default values
AHA_PathActor::AHA_PathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PathComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("PathComponent"));
	RootComponent = PathComponent;
}

// Called when the game starts or when spawned
void AHA_PathActor::BeginPlay()
{
	Super::BeginPlay();
	
}


