// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPS_Network/FPS_NetworkCharacter.h"
#include "NoteBookComponent.generated.h"

USTRUCT(BlueprintType)
struct FInfNode
{
	GENERATED_BODY()
public:
	//信息的正文
	UPROPERTY()
	FString log;
	//信息的编号
	UPROPERTY()
	int ID;
	//信息指向的玩家
	UPROPERTY()
	AFPS_NetworkCharacter* TargetActor;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_NETWORK_API UNoteBookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNoteBookComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FInfNode> NoteArray;

		
};
