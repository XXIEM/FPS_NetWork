// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "PipelineSplineComponent.generated.h"

USTRUCT(BlueprintType)
struct FPipelineGenerationInfo
{
	GENERATED_BODY()
	//控制生成管道曲线的个数 越大管道越平滑
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SplinePointNum = 10;
	//控制管道的半径
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PipelineRadius = 50.0;
	//控制管道的横截面圆的点数
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PipelinePointNum = 16;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExtrudeDistance = 10.0;
	//管道是否封口
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsCapped = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class FPS_NETWORK_API UPipelineSplineComponent : public USplineComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPipelineSplineComponent();

	
	UPROPERTY(Category="PipelineGeneration", BlueprintReadWrite, EditAnywhere)
	FPipelineGenerationInfo PipelineGenerationInfo;
};
