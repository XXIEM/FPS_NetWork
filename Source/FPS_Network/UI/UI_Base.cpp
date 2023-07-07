// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"

UUI_Base::UUI_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

AFPS_NetworkCharacter* UUI_Base::UI_GetFPSCharacterBase()
{
	if(APlayerController* InPlayerControler = GetWorld()->GetFirstPlayerController<APlayerController>())
	{
		if(AFPS_NetworkCharacter* InCharacter = InPlayerControler->GetPawn<AFPS_NetworkCharacter>())
		{
			return  InCharacter;
		}
	}
	return nullptr;
}
