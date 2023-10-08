// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StickyNodeInfoComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI_StickyNotePannel.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FUpdateUIDelegate, TArray<FStickyNodeInfo>);
UCLASS()

class STICKYNOTESSYSTEM_API UUI_StickyNotePannel : public UUserWidget
{
	GENERATED_BODY()

public:
	static FUpdateUIDelegate UpdateUIDelegate;//UI更新委托

	// 实现更新UI的静态函数，接受一个结构体数组作为参数
	static void UpdateUI(TArray<FStickyNodeInfo> StickyNodes);

	static void TriggerUpdateUI(TArray<FStickyNodeInfo> StickyNodes);
	
};
