// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskSubSystem.h"

bool UTaskSubSystem::TaskComplete(FString TaskName)
{
	for(int i = 0;i < TaskList_Array.Num();i++)
	{
		if(TaskName == TaskList_Array[i].TaskName)
		{
			CompletedTask = TaskList_Array[i];
			break;
		}
	}

	if(CompletedTask.score != 0)
	{
		return true;
	}
	else return false;
}

bool UTaskSubSystem::ModifyScore(FTaskNode TaskCompleted)
{
	
	return true;
}

bool UTaskSubSystem::ApplyScoreToEco(FTaskNode TaskCompleted)
{

	return true;
}

//依据TaskName添加节点
bool UTaskSubSystem::AddNode(FString TaskName)
{
	FTaskNode NewNode;
	NewNode.TaskName = TaskName;
	TaskList_Array.Add(NewNode);
}
