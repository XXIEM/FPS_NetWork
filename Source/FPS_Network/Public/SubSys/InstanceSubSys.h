// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "UnrealString.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InstanceSubSys.generated.h"

class FString;

/**
 * 
 */
UCLASS(Abstract)
class FPS_NETWORK_API UInstanceSubSys : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	public:
    	//是否创建这个子系统
    	virtual bool ShouldCreateSubsystem(UObject* Outer) const;
    	//初始化
    	virtual void Initialize(FSubsystemCollectionBase& Collection);
    	//销毁
    	virtual void Deinitialize();
	
	
};



