// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
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
	//UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=DT,meta = (AllowPrivateAccess = "true") )
	//UDataTable* DataTableUtils;

	


};
