// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Kismet/KismetSystemLibrary.h"

bool FInventoryItem::IsValid()
{
	if(FPSItem && ItemCount>0)
	{
		return true;
	}
	return false;
}

void FInventoryItem::ResetSelf()
{
	FPSItem = NULL;
	ItemCount = 0;
}

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	FPS_NetworkCharacter = Cast<AFPS_NetworkCharacter>(GetOwner());
	if(InventoryItems.Num()==0)
	{
		for(SIZE_T i=0;i<4;i++)
		{
			InventoryItems.Add(FInventoryItem());
			
		}
	}
	InventoryItemChanged(InventoryItems);
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddInventoryItem(FInventoryItem NewItem)
{
	
	//只在服务器操作数据
	if(GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		if(!NewItem.IsValid())
		{
			UE_LOG(LogTemp,Warning,TEXT("NewItem是空指针"));
			return false;
		}

		bool bFind = false;
		//遍理找有没有一样的物品，有就叠加
		for(SIZE_T i = 0;i<InventoryItems.Num();i++)
		{
			if(InventoryItems[i].FPSItem == NewItem.FPSItem)
			{
				InventoryItems[i].ItemCount+=NewItem.ItemCount;
				
				//FPS_NetworkCharacter->CurrentInventoryIndex=i;
				//通知UI
				InventoryItemChanged(InventoryItems);
				return true;
			}
		}
		//遍历找空位置
		for(SIZE_T i = 0;i<InventoryItems.Num();i++)
		{
			if(!InventoryItems[i].FPSItem)
			{
				InventoryItems[i]=NewItem;
				//FPS_NetworkCharacter->CurrentInventoryIndex = i;
				//通知UI
				InventoryItemChanged(InventoryItems);
				return true;
			}
		}
	}
	return false;//物品栏满
}

bool UInventoryComponent::AddInventoryItemByIndex(FInventoryItem NewItem, int32 Index_Add)
{
		//只在服务器操作数据
	if(GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		if(!NewItem.IsValid())
		{
			UE_LOG(LogTemp,Warning,TEXT("NewItem是空指针"));
			return false;
		}

	
		//遍历找空位置
		for(SIZE_T i = 0;i<InventoryItems.Num();i++)
		{
			if(!InventoryItems[i].FPSItem && i==Index_Add)
			{
				InventoryItems[i]=NewItem;
				//FPS_NetworkCharacter->CurrentInventoryIndex = i;
				//通知UI
				InventoryItemChanged(InventoryItems);
				return true;
			}
		}
	}
	return false;//物品栏满
}

void UInventoryComponent::RemoveInventoryItem(int32 Index_Remove)
{
	InventoryItems[Index_Remove].ResetSelf();
	InventoryItemChanged(InventoryItems);
	
}

void UInventoryComponent::RemoveInventoryNewItem(FInventoryItem NewItem)
{
	for(SIZE_T i = 0;i<InventoryItems.Num();i++)
	{
		if(InventoryItems[i].FPSItem == NewItem.FPSItem)
		{
			InventoryItems[i].ItemCount -= NewItem.ItemCount;
			if(InventoryItems[i].ItemCount<0)
			{
				InventoryItems[i].ResetSelf();
			}
			InventoryItemChanged(InventoryItems);
			break;
		}
	}
}

void UInventoryComponent::SwapInventoryItem(int32 Index_i, int32 Index_j)
{
	InventoryItems.Swap(Index_i,Index_j);
	InventoryItemChanged(InventoryItems);
}

UClass* UInventoryComponent::Get_WeaponBP(int Index_i)
{
	if(InventoryItems[Index_i].FPSItem!=nullptr)
	{
		return InventoryItems[Index_i].FPSItem->WeaponBP;
	}
	return nullptr;

}

UClass* UInventoryComponent::Get_WeaponPickUp(int Index_i)
{
	if(InventoryItems[Index_i].FPSItem!=nullptr)
	{
		return InventoryItems[Index_i].FPSItem->WeaponPickUp;
	}
	return nullptr;

}

int UInventoryComponent::FindNextExistWeapon()
{
	for(SIZE_T i=0;i<4;i++)
	{
		if(InventoryItems[i].FPSItem!=nullptr)
		{
			return i;
			break;
		}
	}
	return -1;
}




void UInventoryComponent::InventoryItemChanged_Implementation(const TArray<FInventoryItem>& InInventoryItems)
{
	OnInventoryItemChanged.Broadcast(InventoryItems);
}

