// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSAssetManager.h"
#include "FPSItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API UWeaponItem : public UFPSItem
{
	GENERATED_BODY()
public:
	UWeaponItem()
	{
		ItemType = UFPSAssetManager::WeaponItemType;
	}
};
