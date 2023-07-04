// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Network/Public/PlacementMode/PlacementPSComponentBase.h"


// Sets default values for this component's properties
UPlacementPSComponentBase::UPlacementPSComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlacementPSComponentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlacementPSComponentBase, PlacementActors);
}


// Called when the game starts
void UPlacementPSComponentBase::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UPlacementPSComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

