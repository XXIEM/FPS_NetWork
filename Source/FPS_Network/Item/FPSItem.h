// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FPS_Network/Weapon/FPS_WeaponBase.h"
#include "FPSItem.generated.h"

/**
 * 
 */

UCLASS(Abstract,BlueprintType)
class FPS_NETWORK_API UFPSItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFPSItem()
		:MaxCount(1)
	{}

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Item,meta = (AllowPrivateAccess = "true"))
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Item,meta = (AllowPrivateAccess = "true"))
	FText ItemName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Item,meta = (AllowPrivateAccess = "true"))
	FText ItemDiscription;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Item,meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Max,meta = (AllowPrivateAccess = "true"))
	int32 MaxCount;
	

	UFUNCTION(BlueprintCallable,BlueprintPure,Category=Max)
	bool IsConsumable() const;

	UFUNCTION(BlueprintCallable,Category=Item)
	FString GetIdentifierString() const;

	//重载save type
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};
