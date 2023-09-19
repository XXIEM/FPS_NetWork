// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttribute.h"

void UBasicAttribute::MulticastRageChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{
	
}

void UBasicAttribute::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	
}

bool UBasicAttribute::Kill(AActor* InstigatorActor)
{
	return false;
}

bool UBasicAttribute::IsAlive() const
{
	return Health.GetBaseValue() > 0;
}

void UBasicAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	//生命值
	if(Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health,MaxHealth,NewValue,GetHealthAttribute());
	}
	//护盾
	if(Attribute == GetMaxArmorAttribute())
	{
		AdjustAttributeForMaxChange(Armor,MaxArmor,NewValue,GetArmorAttribute());
	}

}

void UBasicAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//生命值
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.0f,GetMaxHealth()));
	}
	//护盾
	if(Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(),0.0f,GetMaxArmor()));
	}
	
}

void UBasicAttribute::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}
