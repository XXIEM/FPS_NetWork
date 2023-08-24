// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSItem.h"

bool UFPSItem::IsConsumable() const
{
	if(MaxCount<=0)
	{
		return true;
	}
	return false;
}

FString UFPSItem::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UFPSItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType,GetFName());
}
