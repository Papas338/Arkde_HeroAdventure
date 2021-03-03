// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HS_MainMenuButton.generated.h"

UENUM(Blueprintable)
enum class EHA_ButtonStyleType : uint8
{
	ButtonStyleType_Mouse			UMETA(DisplayName = "Selected by Mouse"),
	ButtonStyleType_KeySelected		UMETA(DisplayName = "Selected by Keyboard"),
	ButtonStyleType_KeyNoSelected	UMETA(DisplayName = "Not Selected by Keyboard")
};
/**
 * 
 */
UCLASS()
class ARKDE_HEROADVENTURE_API UHS_MainMenuButton : public UButton
{
	GENERATED_BODY()

public:
	UHS_MainMenuButton();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu Button")
		float CheckFocusRate;

	FTimerHandle TimerHandle_CheckFocus;

protected:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void Start();

	void CheckFocus();

	void SetButtonStyle(EHA_ButtonStyleType NewStyleType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void BP_SetButtonStyle(EHA_ButtonStyleType NewStyleType);

};
