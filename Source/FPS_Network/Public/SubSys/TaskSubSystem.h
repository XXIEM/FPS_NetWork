// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstanceSubSys.h"
#include "TaskSubSystem.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTaskNode
{
	GENERATED_BODY()
	FTaskNode()
	{
		TaskName = "";
		score = 0;
	}
	
	UPROPERTY(EditAnywhere)
	FString TaskName;
	
	UPROPERTY(EditAnywhere)
	int score;
	
};

UCLASS(Blueprintable)

class FPS_NETWORK_API UTaskSubSystem : public UInstanceSubSys
{
	GENERATED_BODY()
public:
	//完成任务
	UFUNCTION(BlueprintCallable, Category="Task")
	bool TaskComplete(FString TaskName);
	
	//对分数子系统的通讯
	UFUNCTION(BlueprintCallable, Category="Task")
	bool ModifyScore(FTaskNode TaskCompleted);
	
	//对经济子系统的通讯
	UFUNCTION(BlueprintCallable, Category="Task")
	bool ApplyScoreToEco(FTaskNode TaskCompleted);

	//添加节点
	UFUNCTION(BlueprintCallable, Category="Task")
	bool AddNode(FString TaskName);  

public:
	//任务清单
	UPROPERTY(BlueprintReadWrite, Category="Task")
	TArray<FTaskNode> TaskList_Array;
	
	//完成任务的暂存变量
	UPROPERTY(BlueprintReadWrite, Category="Task")
	FTaskNode CompletedTask;
	
};
 