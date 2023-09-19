// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_FuncLib.h"

// Sets default values
AFPS_FuncLib::AFPS_FuncLib()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AFPS_FuncLib::SetMaxWalkspeed(ACharacter* Character, float Speed)
{
	Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AFPS_FuncLib::SetMaxCrouchspeed(ACharacter* Character, float Speed)
{
	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = Speed;
}

FRotator AFPS_FuncLib::FindLookAtRotator(FVector Start,FVector Target)
{
	return UKismetMathLibrary::FindLookAtRotation(Start,Target);
}

