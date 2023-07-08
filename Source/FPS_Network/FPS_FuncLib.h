// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPS_FuncLib.generated.h"

UCLASS()
class FPS_NETWORK_API AFPS_FuncLib : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS_FuncLib();


	//设置角色最大速度
	UFUNCTION(BlueprintCallable)
	static void SetMaxWalkspeed(ACharacter* Character,float Speed);

	//获取look at旋转
	UFUNCTION(BlueprintCallable)
	static FRotator FindLookAtRotator(FVector Start,FVector Target) ;
};
