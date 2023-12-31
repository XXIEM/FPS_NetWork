// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "InteractiveSystem/Public/WindFieldComponent.h"
#include "WindFieldBase.generated.h"

UCLASS()
class INTERACTIVESYSTEM_API AWindFieldBase : public AFieldSystemActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWindFieldBase();
	UPROPERTY(meta=(ExposeOnSpawn),EditAnywhere,BlueprintReadWrite,Category="WindFieldBase")
	TObjectPtr<UPrimitiveComponent> MeshAttached;

	UPROPERTY(meta=(ExposeOnSpawn),EditAnywhere,BlueprintReadWrite,Category="WindFieldBase")
	FWindFieldGenerationInfo WindFieldGenerationInfo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="WindFieldBase")
	void AddWindField(UPrimitiveComponent* InMeshAttached,const FWindFieldGenerationInfo& GenerationInfo);

};
