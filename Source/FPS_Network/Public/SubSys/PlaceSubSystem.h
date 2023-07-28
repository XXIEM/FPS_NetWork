// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstanceSubSys.h"
#include "PlaceSubSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPS_NETWORK_API UPlaceSubSystem : public UInstanceSubSys
{
	GENERATED_BODY()
public:

	//放置模式初始化
	UFUNCTION(BlueprintCallable)
	void InitPlaceMode();
};
