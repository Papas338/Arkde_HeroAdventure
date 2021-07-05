// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HA_Character.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AHA_LaunchPad::AHA_LaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Component initialization
	HitboxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxComponent"));
	HitboxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitboxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitboxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = HitboxComponent;

	LaunchPadComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadComponent"));
	LaunchPadComponent->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArowComponent"));
	ArrowComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrowComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHA_LaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHA_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AHA_LaunchPad::JumpPadAction();
}

//Detect if a player is on the LaunchPad
void AHA_LaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter)) {
			Player = OverlappedCharacter;
			bIsOverlapped = true;
			BP_Collision();
		}
	}
}

//Detect if a player has left the LaunchPad
void AHA_LaunchPad::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (IsValid(OtherActor)) {
		AHA_Character* OverlappedCharacter = Cast<AHA_Character>(OtherActor);
		if (IsValid(OverlappedCharacter)) {
			BP_CollisionEnd();
			bIsOverlapped = false;
		}
	}
}

//Executes the launch
void AHA_LaunchPad::JumpPadAction()
{
	if (bIsOverlapped == false)
	{
		return;
	}
	if (Player->bIsDoingAction)
	{
		Player->LaunchCharacter(GetLaunchDirection(), true, true);
	}
}

//Calculate the direction where the player is going to be throw towards
FVector AHA_LaunchPad::GetLaunchDirection()
{
	//The direction has been manually calculated since the vector given by .Vector()
	//was not allowing a direction that the LaunchCharacter() could use
	x = FMath::Sin(FMath::DegreesToRadians(GetActorRotation().Yaw + 90));
	y = FMath::Cos(FMath::DegreesToRadians(GetActorRotation().Yaw + 90));
 	LaunchDirection.X = x * 1000;
 	LaunchDirection.Y = -y * 1000;
 	LaunchDirection.Z = 1000;
	return LaunchDirection;
}