// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StickyNodeInfoComponent.generated.h"


USTRUCT(BlueprintType)
struct FStickyNodeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=StickyNote)
	FString Title;//线索标签标题

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=StickyNote)
	FString Description;//线索标签内容

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=StickyNote)
	UTexture2D* ItemIcon;//线索标签图片
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class STICKYNOTESSYSTEM_API UStickyNodeInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStickyNodeInfoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=StickyNote)
	TArray<FStickyNodeInfo> StickyNodes;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	
};
