// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_StickyNotePannel.h"


void UUI_StickyNotePannel::UpdateStickyNoteUI(const FStickyNodeInfo& StickyNodeInfo)
{
	StickyNodeInfos.Add(StickyNodeInfo);
	UE_LOG(LogTemp,Warning,TEXT("BoardCast!!!"));
}

FStickyNoteEvent& UUI_StickyNotePannel::AddMultiDynamicDelegate()
{
	
	return OnStickyNoteEvent;
}

void UUI_StickyNotePannel::NativeConstruct()
{
	Super::NativeConstruct();

	OnStickyNoteEvent.AddDynamic(this,&UUI_StickyNotePannel::UpdateStickyNoteUI);
}
