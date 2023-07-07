// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventoryPannel.h"

#include "Util/ColorConstants.h"


void UUI_InventoryPannel::NativeConstruct()
{
	Super::NativeConstruct();
	//去角色里面绑定好信息
	if(AFPS_NetworkCharacter* InCharacter = UI_GetFPSCharacterBase())
	{
		InCharacter->GetInventoryComponent()->OnInventoryItemChanged.AddUObject(this,&UUI_InventoryPannel::OnInventoryChanged);
	}
}

void UUI_InventoryPannel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

//绑定是客户端的组件上的代理，但是参数是服务端传过来的
void UUI_InventoryPannel::OnInventoryChanged(TArray<FInventoryItem> InInventoryItems)
{
	if(InventoryArray->GetChildrenCount()==0)
	{
		for(SIZE_T i=0;i<1;i++)
		{
			for(SIZE_T j=0;j<4;j++)
			{
				if(UUI_InventorySlot* SlotWidght = CreateWidget<UUI_InventorySlot>(GetWorld(),InventoryClass))
				{
					//1~4分别对应的元素
					SlotWidght->InventoryId = i * 4 + j;
					if(UUniformGridSlot* GridSlot = InventoryArray->AddChildToUniformGrid(SlotWidght,i,j))
					{
						
					}
				}
			}
		}
	}

	if(InInventoryItems.Num()>0)
	{
		for(SIZE_T i=0;i<1;i++)
		{
			for(SIZE_T j=0;j<4;j++)
			{
				if(UUI_InventorySlot* InSlot = Cast<UUI_InventorySlot>(InventoryArray->GetChildAt(i * 4 + j)))
				{
					//数组里有数据就去更新
					if(InInventoryItems[i * 4 + j].IsValid())
					{
						InSlot->Num->SetText(FText::FromString(FString::FromInt(InInventoryItems[i * 4 + j].ItemCount)));
						InSlot->Num->SetVisibility(ESlateVisibility::Visible);

						InSlot->SlotIcon->SetBrushFromTexture(InInventoryItems[i * 4 + j].FPSItem->ItemIcon);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Visible);
						
					}
					else//没有就隐藏
					{
						InSlot->Num->SetVisibility(ESlateVisibility::Hidden);
						InSlot->SlotIcon->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
		}
	}
}
