// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HA_Weapon.h"
#include "GameFramework/Character.h"

// Sets default values
AHA_Weapon::AHA_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHA_Weapon::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AHA_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Executes functions related with every weapon when an attack is executed
void AHA_Weapon::StartWeaponAction()
{

}

//Executes functions related with every weapon when an attack is finished
void AHA_Weapon::StopWeaponAction()
{

}

//Determines the owner for the weapon that is using the code
void AHA_Weapon::CurrentWeaponOwner(ACharacter* WeaponOwner)
{
	SetOwner(WeaponOwner);
	CurrentOwner = WeaponOwner;
}

