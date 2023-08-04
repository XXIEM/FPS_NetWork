// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_WeaponBase.h"

#include <string>

#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AFPS_WeaponBase::AFPS_WeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> TableType(TEXT("/Script/Engine.DataTable'/Game/Game/Weapon/Data/DataTable/WeaponData.WeaponData'"));
	if (TableType.Succeeded())
	{
		WeaponDataTable = TableType.Object;
	}
	

}

// Called when the game starts or when spawned
void AFPS_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	//DataTableUtils->RowStruct =
	WeaponStructArray = DTtoArray(WeaponDataTable);
	WeaponChildStruct = GetWeaponStructFromIndex(WeaponIndex);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s %f %f %f %d"), *WeaponChildStruct.WeaponName,WeaponChildStruct.BulletDamage,WeaponChildStruct.FireFrequency,WeaponChildStruct.RelordSpeed,WeaponChildStruct.BulletNum));

	
}

// Called every frame
void AFPS_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FWeaponStruct> AFPS_WeaponBase::DTtoArray(UDataTable* InDataTable)
{
	TArray<FWeaponStruct> StructInstanceArray;
	
	for (FName RowName : InDataTable->GetRowNames())
	{
		FWeaponStruct* WeaponStructInstance =  InDataTable->FindRow<FWeaponStruct>(RowName,TEXT("Row Name"));
		StructInstanceArray.Add(*WeaponStructInstance);
	}

	return StructInstanceArray;
}

FWeaponStruct AFPS_WeaponBase::GetWeaponStructFromIndex(int Index_i)
{
	for(SIZE_T i=0;i<WeaponStructArray.Num();i++)
	{
		if(i==Index_i)
		{
			return WeaponStructArray[i];
			break;
		}
	}
	return FWeaponStruct();
}


