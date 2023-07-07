// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_WeaponBase.h"

#include "Engine/DataTable.h"

// Sets default values
AFPS_WeaponBase::AFPS_WeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AFPS_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	//DataTableUtils->RowStruct = 
}

// Called every frame
void AFPS_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

