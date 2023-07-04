// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Classes/Net/Serialization/FastArraySerializer.h"
#include "Net/UnrealNetwork.h"
#include "PlacementPSComponentBase.generated.h"


USTRUCT(BlueprintType)
struct FPlacementActorInfo : public FFastArraySerializerItem 
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FName ActorName = NAME_None;
	UPROPERTY(BlueprintReadWrite)
	uint8 Num = 0;

	bool operator == (const FPlacementActorInfo& B)const
	{
		return  this->ActorName == B.ActorName;
	}

	FPlacementActorInfo()
	{
		
	}
	FPlacementActorInfo(FName InName,uint8 InNum =0)
	{
		ActorName = InName;
		Num = InNum;
	}

	// void PreReplicatedRemove(const struct FPlacementActorArray& InArraySerializer);
	// void PostReplicatedAdd(const struct FPlacementActorArray& InArraySerializer);
	// void PostReplicatedChange(const struct FPlacementActorArray& InArraySerializer);
};

USTRUCT(BlueprintType)
struct FPlacementActorArray : public  FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FPlacementActorInfo> Items;
	
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FPlacementActorInfo, FPlacementActorArray>( Items, DeltaParms, *this );
	}

	
};

template<>
struct TStructOpsTypeTraits< FPlacementActorArray > : public TStructOpsTypeTraitsBase2< FPlacementActorArray >
{
	enum 
	{
		WithNetDeltaSerializer = true,
   };
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_NETWORK_API UPlacementPSComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlacementPSComponentBase();
	
	UPROPERTY(Replicated,EditDefaultsOnly,BlueprintReadWrite)
	FPlacementActorArray PlacementActors;
private:
	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;
protected:
	/**
	 * @brief This must be called if you add or change an item in the array
	 * @param Item 
	 */
	UFUNCTION(BlueprintCallable,DisplayName="MarkItemDirty")
	void K2_MarkItemDirty(FPlacementActorInfo& Item)
	{
		PlacementActors.MarkItemDirty(Item);
	}

	/**
	 * @brief This must be called if you just remove something from the array
	 */
	UFUNCTION(BlueprintCallable,DisplayName="RemoveItemFromPlacementActors")
	void K2_RemoveItemFromPlacementActors(int Index)
	{
		PlacementActors.Items.RemoveAtSwap(Index);
		PlacementActors.MarkArrayDirty();
	}
	
public:
	UFUNCTION(BlueprintCallable,DisplayName= "FindIndexInPlacementActors")
	int K2_FindIndexInPlacementActors(const FName& InName)
	{
		int Index = INDEX_NONE;
		Index = PlacementActors.Items.IndexOfByPredicate([&](const FPlacementActorInfo& Item){return Item.ActorName == InName;});
		return Index;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
