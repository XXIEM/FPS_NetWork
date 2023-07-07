// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FPS_Network/FPS_GameType.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API UUI_InventorySlot : public UUI_Base
{
	GENERATED_BODY()
	UUI_InventorySlot(const FObjectInitializer& ObjectInitializer);

	//需要get/set方法


	
public:
	ESlotType SlotType;

	UPROPERTY()
	int32 InventoryId;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Num;

	UPROPERTY(meta=(BindWidget))
	UImage* SlotIcon;
	
	
};
