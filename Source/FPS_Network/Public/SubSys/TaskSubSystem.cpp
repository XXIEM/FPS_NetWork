// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskSubSystem.h"

#include "EcoSubSystem.h"

bool UTaskSubSystem::TaskComplete(FText TaskName, FString PlayerName, int TaskScore)
{
	int DeltaEco;
	
	ScoreSysPtr->AddScore(PlayerName, TaskScore);

	DeltaEco = TaskScore * EcoMagnification;
	
	EcoSysPtr->ModifyEco(PlayerName, DeltaEco);
	return true;
}

bool UTaskSubSystem::GetScoreSubSys(UScoreSubSystem* TargetPtr)
{
	ScoreSysPtr = TargetPtr;
	if(ScoreSysPtr != nullptr) UE_LOG(LogTemp,Warning,TEXT("已连接上ScoreSubSys"));
	return true;
}

bool UTaskSubSystem::GetEcoSubSys(UEcoSubSystem* TargetPtr)
{
	EcoSysPtr = TargetPtr;
	if(EcoSysPtr != nullptr) UE_LOG(LogTemp,Warning,TEXT("已连接上EcoSubSys"));
	return true;
}