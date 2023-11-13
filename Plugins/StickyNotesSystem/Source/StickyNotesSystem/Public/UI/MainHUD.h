// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_StickyNotePannel.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class STICKYNOTESSYSTEM_API AMainHUD : public AHUD
{
	GENERATED_BODY()


public:
	//线索板UI
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="StickyNodeInfo",meta=(AllowPrivateAccess))
	UUI_StickyNotePannel* StickyNotePannel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="StickyNodeInfo",meta=(AllowPrivateAccess))
	UUserWidget* RelordUI;
	
};
