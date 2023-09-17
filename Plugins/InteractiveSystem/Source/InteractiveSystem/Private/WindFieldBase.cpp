// Fill out your copyright notice in the Description page of Project Settings.


#include "WindFieldBase.h"


// Sets default values
AWindFieldBase::AWindFieldBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWindFieldBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWindFieldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddWindField(MeshAttached,WindFieldGenerationInfo);
}







