// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_StickyNotePannel.h"


FUpdateUIDelegate UUI_StickyNotePannel::UpdateUIDelegate;


void UUI_StickyNotePannel::UpdateUI(TArray<FStickyNodeInfo> StickyNodes)
{
	
}

void UUI_StickyNotePannel::TriggerUpdateUI(TArray<FStickyNodeInfo> StickyNodes)
{
	if (UpdateUIDelegate.IsBound())
	{
		UpdateUIDelegate.Execute(StickyNodes);
	}
}
