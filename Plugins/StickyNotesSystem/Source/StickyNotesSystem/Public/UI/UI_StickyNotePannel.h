// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StickyNodeInfoComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI_StickyNotePannel.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStickyNoteEvent, const FStickyNodeInfo&, StickyNodeInfo);
UCLASS()


class STICKYNOTESSYSTEM_API UUI_StickyNotePannel : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="StickyNodeInfo",meta=(AllowPrivateAccess))
	TArray<FStickyNodeInfo> StickyNodeInfos;

	UPROPERTY(BlueprintAssignable)
	FStickyNoteEvent OnStickyNoteEvent;

public:
	UFUNCTION()
	void UpdateStickyNoteUI(const FStickyNodeInfo& StickyNodeInfo);

	//动态的多播绑定
	FStickyNoteEvent& AddMultiDynamicDelegate();

	virtual void NativeConstruct() override;
};
