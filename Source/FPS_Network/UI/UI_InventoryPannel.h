// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"
#include "UI_InventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "../Component/InventoryComponent.h"
#include "UI_InventoryPannel.generated.h"

/**
 * 
 */

UCLASS()

class FPS_NETWORK_API UUI_InventoryPannel : public UUI_Base
{
	GENERATED_BODY()

	//框框，用来装元素
	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* InventoryArray;

	UPROPERTY(EditDefaultsOnly,Category=UI)
	TSubclassOf<UUI_InventorySlot> InventoryClass;

public:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//用来接收物品栏发来的消息
	UFUNCTION()
	void OnInventoryChanged(TArray<FInventoryItem> InInventoryItems);
};
