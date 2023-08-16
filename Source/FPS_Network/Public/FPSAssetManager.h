// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FPS_Network/Item/FPSItem.h"
#include "FPSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API UFPSAssetManager : public UAssetManager
{
	GENERATED_BODY()


public:
	UFPSAssetManager(){}

	virtual void StartInitialLoading() override;

	//static的物品栏Item的type
	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType MissileItemType;
	//任务类的type
	static const FPrimaryAssetType TaskItemType;

	//Return当前manager的object
	static UFPSAssetManager& Get();

	UFPSItem* ForceLordItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true );
	
};
