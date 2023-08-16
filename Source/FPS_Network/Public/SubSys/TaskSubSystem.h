// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EcoSubSystem.h"
#include "InstanceSubSys.h"
#include "ScoreSubSystem.h"
#include "TaskSubSystem.generated.h"
/**
 * 
 */

// USTRUCT(BlueprintType)
// struct FTaskNode
// {
// 	GENERATED_BODY()
// 	FTaskNode()
// 	{
// 		TaskName = "";
// 		score = 0;
// 	}
// 	
// 	UPROPERTY(EditAnywhere)
// 	FString TaskName;
// 	
// 	UPROPERTY(EditAnywhere)
// 	int score;
// 	
// };

UCLASS(Blueprintable)

class FPS_NETWORK_API UTaskSubSystem : public UInstanceSubSys
{
	GENERATED_BODY()
public:
	//完成任务
	UFUNCTION(BlueprintCallable, Category="Task")
	bool TaskComplete(FText TaskName, FString PlayerName, int TaskScore);

	//绑定分数子系统
	UFUNCTION(BlueprintCallable)
	bool GetScoreSubSys(UScoreSubSystem* TargetPtr);

	//绑定经济子系统
	UFUNCTION(BlueprintCallable)
	bool GetEcoSubSys(UEcoSubSystem* TargetPtr);

public:

	
	//完成任务的暂存变量
	UPROPERTY(BlueprintReadWrite, Category="Task")
	FString CompletedTask;

	//绑定的分数子系统
	UPROPERTY(BlueprintReadWrite)
	UScoreSubSystem* ScoreSysPtr;

	//绑定的经济子系统
	UPROPERTY(BlueprintReadWrite)
	UEcoSubSystem* EcoSysPtr;

	//经济倍率
	UPROPERTY(BlueprintReadWrite)
	float EcoMagnification = 1.0;
	
};
 