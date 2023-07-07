// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS_Network/FPS_NetworkCharacter.h"
#include "UI_Base.generated.h"

/**
 * 
 */

UCLASS()
class FPS_NETWORK_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()
public:
	UUI_Base(const FObjectInitializer& ObjectInitializer);

protected:
	AFPS_NetworkCharacter* UI_GetFPSCharacterBase();
};
