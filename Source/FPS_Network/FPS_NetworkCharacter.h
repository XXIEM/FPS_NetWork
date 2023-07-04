// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "BasicAttribute.h"
#include "Components/TimelineComponent.h"
#include "FPS_NetworkCharacter.generated.h"


UCLASS(config=Game)
class AFPS_NetworkCharacter : public ACharacter
{
	GENERATED_BODY()

	
	/** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	//** Aim Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	//** Chouch/Slide Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchSLideAction;

	//** Fire Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
public:
	AFPS_NetworkCharacter();


public:
	//ASC组件
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AbilityComp")
	UAbilitySystemComponent* AbilityComp;


	//角色属性
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AbilityComp")
	UBasicAttribute* BAS; 

	//返回能力组件
	UFUNCTION(BlueprintCallable,Category="AbilityComp")
	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Aiming input */
	UFUNCTION(BlueprintImplementableEvent)
	void StartAim();

	UFUNCTION(BlueprintImplementableEvent)
	void EndAim();

	/** Called for Chouch/Slide input */
	UFUNCTION(BlueprintImplementableEvent)
	void StartCrouchSlide();

	UFUNCTION(BlueprintImplementableEvent)
	void EndcrouchSlide();

	/** Called for Sprint input */
	UFUNCTION(BlueprintImplementableEvent)
	void StartSprint();

	UFUNCTION(BlueprintImplementableEvent)
	void EndSprint();

	/** Called for Fire input */
	UFUNCTION(BlueprintImplementableEvent)
	void StartFire();

	UFUNCTION(BlueprintImplementableEvent)
	void EndFire();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();



protected:
	//初始GA
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityComp")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilitys;


	//初始GE
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityComp")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;




public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

