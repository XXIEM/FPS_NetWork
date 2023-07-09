// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSAssetManager.h"
#include "FPSItem.h"
#include "MissileItem.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API UMissileItem : public UFPSItem
{
	GENERATED_BODY()

public:
	UMissileItem()
	{
		ItemType = UFPSAssetManager::MissileItemType;
	}
};
