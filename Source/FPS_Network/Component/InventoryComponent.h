// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPS_Network/FPS_NetworkCharacter.h"
#include "FPS_Network/Item/FPSItem.h"
#include "InventoryComponent.generated.h"

class AFPS_NetworkCharacter;
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	FInventoryItem()
		:FPSItem(NULL)
		,ItemCount(0)
	{}
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=InventoryItem)
	UFPSItem* FPSItem;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=InventoryItem)
	int32 ItemCount;

	bool IsValid();

	void ResetSelf();
	
	
	
	
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChangedNative, TArray<FInventoryItem>);//代理
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_NETWORK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<AFPS_NetworkCharacter> FPS_NetworkCharacter;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




public:
//改变物品栏数组的方法	
	//增加新实例
	UFUNCTION(BlueprintCallable,Category=Inventory)
	bool AddInventoryItem(FInventoryItem NewItem);

	//移除数组里的元素
	UFUNCTION(BlueprintCallable,Category=Inventory)
	void RemoveInventoryItem(int32 Index_Remove);

	//移除传进来的对象
	UFUNCTION(BlueprintCallable,Category=Inventory)
	void RemoveInventoryNewItem(FInventoryItem NewItem);

	UFUNCTION(BlueprintCallable,Category=Inventory)
	void SwapInventoryItem(int32 Index_i, int32 Index_j);

	//==========通知UI刷新界面===============
	UFUNCTION(Client,Reliable)
	void InventoryItemChanged(const TArray<FInventoryItem>& InInventoryItems);

	//给UI绑定的代理
	FOnInventoryItemChangedNative OnInventoryItemChanged;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Inventory)
	TArray<FInventoryItem> InventoryItems;//物品栏中的实例数组
};