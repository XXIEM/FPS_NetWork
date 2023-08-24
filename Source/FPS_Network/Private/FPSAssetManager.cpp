// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAssetManager.h"


const FPrimaryAssetType UFPSAssetManager::WeaponItemType = TEXT("Weapon");
const FPrimaryAssetType UFPSAssetManager::MissileItemType = TEXT("Missile");


void UFPSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
}

UFPSAssetManager& UFPSAssetManager::Get()
{
	UFPSAssetManager* This = Cast<UFPSAssetManager>(GEngine->AssetManager);
	if(This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp,Fatal,TEXT("Invalid AssetManager in, must be FPSAssetmanager!"));
		return *NewObject<UFPSAssetManager>();//never call this
	}
	
}

UFPSItem* UFPSAssetManager::ForceLordItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);
	UFPSItem* LoadedItem = Cast<UFPSItem>(ItemPath.TryLoad());
	if(bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed to Load Item!!"));
	}

	return LoadedItem;

}
