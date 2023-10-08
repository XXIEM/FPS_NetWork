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

void UWindFieldComponent::InitializeComponent()
{
	Super::InitializeComponent();
	const auto Owner = GetOwner();
}

void UWindFieldComponent::GenerateWindField_Implementation(TArray<FWindFieldGenerationInfo>& InFieldGenerationInfos,
                                                           UPrimitiveComponent* InTargetMesh)
{
	const auto World = GetWorld();
	check(World);
	check(TargetMesh);
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
