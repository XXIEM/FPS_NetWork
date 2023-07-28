// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSubSystem.h"

bool UScoreSubSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void UScoreSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//可以对一些资源进行初始化
	Super::Initialize(Collection);
}
 
void UScoreSubSystem::Deinitialize()
{
	//这里对资源进行卸载
	Super::Deinitialize();
}

//依据角色名进行加分
bool UScoreSubSystem::Addscore(FString PlayerName, float delta)
{
	for(int i = 0;i<ScoreArray.Num();i++)
	{
		if(ScoreArray[i].PlayerName == PlayerName)
		{
			ScoreArray[i].score += delta;
			break;
		}
	}
	return true;
}

//排名函数，只适用于三个玩家的情况
bool UScoreSubSystem::Ranking(TArray<FScoreNode> ScoreForRanking)
{
	//最高分-最低分玩家序号暂存变量
	int MaxScoreTemp = 0, MinScoreTemp = 0, MidScoreTemp;
	for(int i = 0;i<ScoreArray.Num()-1;i++)
	{
		if(ScoreArray[i+1].score>ScoreArray[MaxScoreTemp].score)
		{
			MaxScoreTemp = i+1;
		}
		else if(ScoreArray[i+1].score < ScoreArray[MinScoreTemp].score)
		{
			MinScoreTemp = i+1;
		}
		else
		{
			MidScoreTemp = i+1;
		}
	}
	//这里还缺少平局判定
	ScoreArray[MaxScoreTemp].Rank = 1;
	ScoreArray[MidScoreTemp].Rank = 2;
	ScoreArray[MinScoreTemp].Rank = 3;
	
	return true;
}

//依据PlayerName添加新节点
bool UScoreSubSystem::AddNode(FString Playername)
{
	FScoreNode NewNode;
	NewNode.PlayerName = Playername;
	ScoreArray.Add(NewNode);
}
