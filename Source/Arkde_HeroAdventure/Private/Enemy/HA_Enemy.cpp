// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HA_Enemy.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "Enemy/Controller/HS_AIControllerNew.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HA_HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/HA_GameMode.h"
#include "Weapons/HA_Weapon.h"
#include "UI/Enemy/HS_EnemyHealthBar.h"

AHA_Enemy::AHA_Enemy()
{
	WidgetHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHealthBarComponent"));
	WidgetHealthBarComponent->SetupAttachment(RootComponent);

	bIsSetToDespawn = false;
}
void AHA_Enemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &AHA_Enemy::HealthChanged);
	MyController = Cast<AHS_AIControllerNew>(GetController());

	
	
	UUserWidget* UserWidget = WidgetHealthBarComponent->GetUserWidgetObject();
	if (IsValid(UserWidget))
	{
		EnemyHealthBar = Cast<UHS_EnemyHealthBar>(UserWidget);
		HealthComponent->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBar, &UHS_EnemyHealthBar::UpdateHealthBar);
		HideHealthBar();
	}
}

void AHA_Enemy::HealthChanged(UHA_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!IsValid(MyController))
	{
		return;
	}

	if (bIsShowingHealthBar)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideHealthBar);
	}
	else
	{
		ShowHealthBar();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideHealthBar, this, &AHA_Enemy::HideHealthBar, 1.0f, false);

	if (HealthComponent->IsDead() && !bIsSetToDespawn)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		MyController->DeactivateAIPerception();

		MyController->UnPossess();

		SetAlerted(false);

		HideHealthBar();

		GameModeReference->AddEnemyKilled();

		if (HasToDestroy())
		{
			bIsSetToDespawn = true;
			SetLifeSpan(5.0f);
			DetachFromControllerPendingDestroy();
		}
	}
	else
	{
		AHA_Weapon* PlayerWeapon = Cast<AHA_Weapon>(DamageCauser);
		if (IsValid(PlayerWeapon))
		{
			MyController->SetReceivingDamage(true);
			AActor* RifleOwner = PlayerWeapon->GetOwner();
			UAISense_Damage::ReportDamageEvent(GetWorld(), this, RifleOwner, Damage, RifleOwner->GetActorLocation(), FVector::ZeroVector);
		}
	}

}

void AHA_Enemy::SetAlerted(bool bValue)
{
	bIsAlerted = bValue;

	if (IsValid(GameModeReference))
	{
		GameModeReference->CheckAlerts();
	}
}

void AHA_Enemy::ShowHealthBar()
{
	bIsShowingHealthBar = true;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void AHA_Enemy::HideHealthBar()
{
	bIsShowingHealthBar = false;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}
