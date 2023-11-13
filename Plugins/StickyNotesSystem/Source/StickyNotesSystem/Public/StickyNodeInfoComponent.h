// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPS_Network/Item/StickyNoteItem.h"
#include "StickyNodeInfoComponent.generated.h"


USTRUCT(BlueprintType)
struct FStickyNodeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Item,meta = (AllowPrivateAccess = "true"))
	FText ItemName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Item,meta = (AllowPrivateAccess = "true"))
	FText ItemDiscription;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Item,meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;
	
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
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=StickyNote)
	FStickyNodeInfo StickyNodeInfo;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//广播事件event
	UFUNCTION(BlueprintCallable)
	void InvokeMultiDynamicDelegate();

	UFUNCTION(BlueprintCallable)
	void SetStickyNote(FStickyNodeInfo StickyNodeInfoIns);
	
};
