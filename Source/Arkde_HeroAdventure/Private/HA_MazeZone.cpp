// Fill out your copyright notice in the Description page of Project Settings.


#include "HA_MazeZone.h"
#include "Components/BoxComponent.h"
#include "Core/HA_GameMode.h"
#include "HA_Character.h"

// Sets default values
AHA_MazeZone::AHA_MazeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxComponent"));
	HitBoxComponent->SetupAttachment(RootComponent);
	HitBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AHA_MazeZone::BeginPlay()
{
	Super::BeginPlay();
	
	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHA_MazeZone::EnterZone);
	HitBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHA_MazeZone::ExitZone);

	GameModeReference = Cast<AHA_GameMode>(GetWorld()->GetAuthGameMode());
}

void AHA_MazeZone::EnterZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHA_Character* PlayerCharacter = Cast<AHA_Character>(OtherActor);
	if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == EHA_CharacterType::CharacterType_Player) {
		bIsInZone = true;
		PlayerCharacter->SetIsInSmallZone(bIsInZone);
		GameModeReference->CheckAlerts();
	}
}

void AHA_MazeZone::ExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHA_Character* PlayerCharacter = Cast<AHA_Character>(OtherActor);
	if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == EHA_CharacterType::CharacterType_Player) {
		bIsInZone = false;
		PlayerCharacter->SetIsInSmallZone(bIsInZone);
		GameModeReference->CheckAlerts();
	}
}


