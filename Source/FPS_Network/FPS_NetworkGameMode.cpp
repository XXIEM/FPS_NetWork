// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_NetworkGameMode.h"
#include "FPS_NetworkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_NetworkGameMode::AFPS_NetworkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
