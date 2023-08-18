// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API ABotAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	virtual void BeginPlay() override;
	
};
