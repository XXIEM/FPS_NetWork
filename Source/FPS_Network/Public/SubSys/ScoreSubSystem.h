// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstanceSubSys.h"
#include "ScoreSubSystem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FScoreNode
{
	GENERATED_BODY()
	FScoreNode()
	{
		score = 0;
		Rank = -1;
	}
	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int score;

	UPROPERTY(BlueprintReadWrite)
	int Rank;
};

UCLASS(Blueprintable)
class FPS_NETWORK_API UScoreSubSystem : public UInstanceSubSys
{
	GENERATED_BODY()

	//是否创建这个子系统
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	//初始化
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	//销毁
	virtual void Deinitialize();

	//添加得分
	UFUNCTION(BlueprintCallable, Category="ScoreManage")
	bool Addscore(FString PlayerName, float delta);
	
	//比较得分排名
	UFUNCTION(BlueprintCallable, Category="ScoreManage")
	bool Ranking(TArray<FScoreNode> ScoreForRanking);

	//添加节点
	UFUNCTION(BlueprintCallable, Category="ScoreManage")
	bool AddNode(FString Playername);  

public:
	//接受和储存玩家分数的容器
	UPROPERTY(BlueprintReadWrite, Category="ScoreManage")
	TArray<FScoreNode> ScoreArray;
	
	//玩家排名暂存变量
	UPROPERTY(BlueprintReadWrite)
	int Rank;
};
