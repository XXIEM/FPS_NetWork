// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "WindFieldComponent.generated.h"

class AWindFieldBase;

USTRUCT(BlueprintType)
struct FWindFieldGenerationInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FName SocketName;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TSubclassOf<AWindFieldBase> SpawnFieldClass;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float VelocityScale = 1.0;
};
class AFieldSystemActor;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIVESYSTEM_API UWindFieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWindFieldComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void GenerateWindField(TArray<FWindFieldGenerationInfo>& InFieldGenerationInfos,UPrimitiveComponent* InTargetMesh);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WildField")
	TArray<FWindFieldGenerationInfo> FieldGenerationInfos;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="WildField")
	TObjectPtr<UPrimitiveComponent> TargetMesh;
	
};
