// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceSubSys.h"

bool UInstanceSubSys::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void UInstanceSubSys::Initialize(FSubsystemCollectionBase& Collection)
{
	//可以对一些资源进行初始化
	Super::Initialize(Collection);
}
 
void UInstanceSubSys::Deinitialize()
{
	//这里对资源进行卸载
	Super::Deinitialize();
}
