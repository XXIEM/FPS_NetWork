// Fill out your copyright notice in the Description page of Project Settings.


#include "WindFieldComponent.h"

#include "ShaderParameterStruct.h"
#include "InteractiveSystem/Public/WindFieldBase.h"


// Sets default values for this component's properties
UWindFieldComponent::UWindFieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWindFieldComponent::BeginPlay()
{
	Super::BeginPlay();
	GenerateWindField_Implementation(FieldGenerationInfos,TargetMesh);
	// ...
	
}

void UWindFieldComponent::GenerateWindField_Implementation(TArray<FWindFieldGenerationInfo>& InFieldGenerationInfos,
	UPrimitiveComponent* InTargetMesh)
{
	const auto World = GetWorld();
	check(World);
	for (const FWindFieldGenerationInfo Info : InFieldGenerationInfos)
	{
		const auto SpawnedActor  = Cast<AWindFieldBase>(World->SpawnActor(Info.SpawnFieldClass.GetDefaultObject()->GetClass()));
		if (SpawnedActor == nullptr)
		{
			return;
		}
		SpawnedActor->AttachToComponent(InTargetMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,Info.SocketName);
		SpawnedActor->MeshAttached = TargetMesh;
		SpawnedActor->WindFieldGenerationInfo = Info;
	}
}

class FTestShader : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FTestShader);
	SHADER_USE_PARAMETER_STRUCT(FTestShader,FGlobalShader);
	
	class FMyShaderPerm : SHADER_PERMUTATION_INT("TEST",1);
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
	END_SHADER_PARAMETER_STRUCT()
};
