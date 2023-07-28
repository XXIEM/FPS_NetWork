// Fill out your copyright notice in the Description page of Project Settings.


#include "EcoSubSystem.h"

bool UEcoSubSystem::ModifyEco(FString PlayerName, int delta)
{
	for(int i = 0; i< PlayerEcoArray.Num(); i++)
	{
		if(PlayerEcoArray[i].PlayerName == PlayerName)
		{
			PlayerEcoArray[i].PlayerEco += delta;
			if(PlayerEcoArray[i].PlayerEco < 0)
			{
				PlayerEcoArray[i].PlayerEco += (delta*-1);
				return false;
			}
			break;
		}
	}
	
	return true;
}

//依据PlayerName添加节点
bool UEcoSubSystem::AddNode(FString Playername)
{
	FPlayerEcoNode NewNode;
	NewNode.PlayerName = Playername;
	PlayerEcoArray.Add(NewNode);
}

