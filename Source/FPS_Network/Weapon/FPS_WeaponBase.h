// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "FPS_WeaponBase.generated.h"


USTRUCT(BlueprintType)
struct  FWeaponStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString WeaponName;

	UPROPERTY(EditAnywhere)
	float BulletSpread;

	UPROPERTY(EditAnywhere)
	float BulletDamage;

	UPROPERTY(EditAnywhere)
	float FireFrequency;
	
	UPROPERTY(EditAnywhere)
    float RelordSpeed;
	

};


UCLASS()
class FPS_NETWORK_API AFPS_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	//枪械的Data Table
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=DT,meta = (AllowPrivateAccess = "true") )
	UDataTable* WeaponDataTable;

	//枪械的UStruct数组
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=DT,meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponStruct> WeaponStructArray;

	//枪械索引
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=DT,meta = (AllowPrivateAccess = "true"))
	int WeaponIndex;

	//子类的UStruct
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=DT,meta = (AllowPrivateAccess = "true"))
	FWeaponStruct WeaponChildStruct;
	
public:

	UFUNCTION(BlueprintCallable,Category=DT, meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponStruct> DTtoArray(UDataTable* InDataTable);

	UFUNCTION(BlueprintCallable,Category=DT, meta = (AllowPrivateAccess = "true"))
	FWeaponStruct GetWeaponStructFromIndex(int Index_i);
	
};
