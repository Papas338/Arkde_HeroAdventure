// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/HS_AIController.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemy/HA_Enemy.h"
#include "Components/HA_HealthComponent.h"


AHS_AIController::AHS_AIController()
{
	WaitingTimeKeyName = "WaitingTime";
	SeeingPlayerKeyName = "bIsSeeingPlayer";
	IsPlayerAliveKeyName = "bIsPlayerAlive";
	//Components creation
}

void AHS_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);

		MyEnemy = Cast<AHA_Enemy>(K2_GetPawn());
		if (IsValid(MyEnemy))
		{
			MyBlackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
			if (IsValid(MyBlackboard))
			{
				MyBlackboard->SetValueAsFloat(WaitingTimeKeyName, 1);
			}
		}
	}
}

/*
void AHS_AIController::UpdateSenses(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* ActorSelected : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		AIPerceptionComponent->GetActorsPerception(ActorSelected, PerceptionInfo);
		AHA_Character* SensedPlayer = Cast <AHA_Character>(ActorSelected);

		if (IsValid(SensedPlayer) && SensedPlayer->GetCharacterType() == EHA_CharacterType::CharacterType_Player)
		{
			for (int i = 0; i <= PerceptionInfo.LastSensedStimuli.Num(); i++)
			{
				switch (i)
				{
				case 0:
					bPlayerStatus = SensedPlayer->HealthComponent->IsDead();
					//Detects if the player is dead or alive
					if (bPlayerStatus)
					{
						MyBlackboard->SetValueAsBool(IsPlayerAliveKeyName, !bPlayerStatus);
						MyBlackboard->SetValueAsBool(SeeingPlayerKeyName, !bPlayerStatus);
					}
					else {
						MyBlackboard->SetValueAsBool(SeeingPlayerKeyName, PerceptionInfo.LastSensedStimuli[i].WasSuccessfullySensed());
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

*/