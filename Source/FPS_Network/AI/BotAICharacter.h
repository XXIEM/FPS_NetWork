// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_Network/FPS_NetworkCharacter.h"
#include "BotAICharacter.generated.h"

class UPawnSensingComponent;
class UUserWidget;

/**
 * 
 */
UCLASS()
class FPS_NETWORK_API ABotAICharacter : public AFPS_NetworkCharacter
{
	GENERATED_BODY()
	
	public:
		ABotAICharacter();
	
		// UPROPERTY()
		//TObjectPtr<USWorldUserWidget> ActiveHealthBar;
    
    	UPROPERTY(EditDefaultsOnly, Category = "UI")
    	TSubclassOf<UUserWidget> HealthBarWidgetClass;
    
    	/* Widget to display when bot first sees a player. */
    	UPROPERTY(EditDefaultsOnly, Category = "UI")
    	TSubclassOf<UUserWidget> SpottedWidgetClass;
    
    	/* Material parameter for Hitflashes */
    	UPROPERTY(VisibleAnywhere, Category = "Effects")
    	FName TimeToHitParamName;
    
    	/* Key for AI Blackboard 'TargetActor' */
    	UPROPERTY(VisibleAnywhere, Category = "Effects")
    	FName TargetActorKey;
    
    	UFUNCTION(BlueprintCallable, Category = "AI")
    	void SetTargetActor(AActor* NewTarget);
    
    	UFUNCTION(BlueprintCallable, Category = "AI")
    	AActor* GetTargetActor() const;
    
    	virtual void PostInitializeComponents() override;
    
    	UFUNCTION()
    	void OnHealthChanged(AActor* InstigatorActor, UBasicAttribute* OwningComp, float NewHealth, float Delta);
    
    	UPROPERTY(VisibleAnywhere, Category = "Components")
    	TObjectPtr<UPawnSensingComponent> PawnSensingComp;
    
    	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    	// TObjectPtr<UBasicAttribute> BAS;
    
    	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    	// TObjectPtr<USActionComponent> ActionComp;
    
    	UFUNCTION()
    	void OnPawnSeen(APawn* Pawn);
    
    	UFUNCTION(NetMulticast, Unreliable)
    	void MulticastPawnSeen();
	
};
