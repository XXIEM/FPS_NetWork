// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSAssetManager.h"
#include "FPSItem.h"
#include "StickyNoteItem.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API UStickyNoteItem : public UFPSItem
{
	GENERATED_BODY()

public:
	UStickyNoteItem()
	{
		ItemType = UFPSAssetManager::StickyNoteItemType;
	}
	
};
