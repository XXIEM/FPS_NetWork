// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstanceSubSys.h"
#include "EcoSubSystem.generated.h"

USTRUCT(BlueprintType)
struct FPlayerEcoNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;
	
	UPROPERTY(BlueprintReadWrite)
	int PlayerEco;
	
};
/**
 * 
 */
UCLASS(Blueprintable)
class FPS_NETWORK_API UEcoSubSystem : public UInstanceSubSys
{
	GENERATED_BODY()

public:
	//改变经济
	UFUNCTION(BlueprintCallable, Category="EcoManage")
	bool ModifyEco(FString PlayerName, int delta);

	//添加节点
	UFUNCTION(BlueprintCallable, Category="EcoManage")
	bool AddNode(FString Playername);  

public:
	//玩家经济列表
	UPROPERTY(BlueprintReadWrite, Category="EcoManage")
	TArray<FPlayerEcoNode> PlayerEcoArray;
	
};
