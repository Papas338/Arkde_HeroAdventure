// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/HS_AIControllerNew.h"
#include "Enemy/HA_Enemy.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Components/HA_HealthComponent.h"

AHS_AIControllerNew::AHS_AIControllerNew()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	WaitingTimeKeyName = "WaitingTime";
	CanSeePlayerKeyName = "bIsSeeingPlayer";
	HasReceivedDamageKeyName = "bHasReceivedDamage";
	TargetLocationKeyName = "TargetLocation";
	IsPlayerAliveKeyName = "bIsPlayerAlive";
}

void AHS_AIControllerNew::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AHS_AIControllerNew::UpdateSenses);

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);
		MyEnemy = Cast<AHA_Enemy>(K2_GetPawn());
		if (IsValid(MyEnemy))
		{
			MyBlackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
			if (IsValid(MyBlackboard))
			{
				MyBlackboard->SetValueAsFloat(WaitingTimeKeyName, MyEnemy->GetWaitingTime());
			}
		}
	}
}

void AHS_AIControllerNew::UpdateSenses(const TArray<AActor*>& UpdatedActors)
{
	if (!IsValid(MyBlackboard))
	{
		return;
	}

	for (AActor* SensedActor : UpdatedActors) {

		FActorPerceptionBlueprintInfo PerceptionInfo;
		AIPerceptionComponent->GetActorsPerception(SensedActor, PerceptionInfo);

		AHA_Character* SensedCharacter = Cast<AHA_Character>(SensedActor);
		if (IsValid(SensedCharacter) && SensedCharacter->GetCharacterType() == EHA_CharacterType::CharacterType_Player)
		{
			for (int i = 0; i < PerceptionInfo.LastSensedStimuli.Num(); i++)
			{
				switch (i)
				{
				case 0:
					MyBlackboard->SetValueAsBool(CanSeePlayerKeyName, PerceptionInfo.LastSensedStimuli[i].WasSuccessfullySensed());
					break;
				case 1:
					UE_LOG(LogTemp, Warning, TEXT("Ouch"))
					MyBlackboard->SetValueAsBool(HasReceivedDamageKeyName, bReceivingDamage);
					if (bReceivingDamage)
					{
						MyBlackboard->SetValueAsVector(TargetLocationKeyName, PerceptionInfo.LastSensedStimuli[i].StimulusLocation);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}
