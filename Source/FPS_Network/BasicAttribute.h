// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "BasicAttribute.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class FPS_NETWORK_API UBasicAttribute : public UAttributeSet
{
	GENERATED_BODY()

public:
	//生命值
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health=100.0f;
	ATTRIBUTE_ACCESSORS(UBasicAttribute,Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth=100;
	ATTRIBUTE_ACCESSORS(UBasicAttribute,MaxHealth);

	//护盾
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Armor=20;
	ATTRIBUTE_ACCESSORS(UBasicAttribute,Armor);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxArmor=100;
	ATTRIBUTE_ACCESSORS(UBasicAttribute,MaxArmor);

	UFUNCTION(NetMulticast, Reliable) // @note: could mark as unreliable once we moved the 'state' out of scharacter (eg. once its cosmetic only)
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Unreliable) // Used for cosmetic changes only
	void MulticastRageChanged(AActor* InstigatorActor, float NewRage, float Delta);

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	void OnHealthChanged();

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,const FGameplayAttributeData& MaxAttribute,float NewMaxValue,const FGameplayAttribute& AffectedAttributeProperty);
	
};
