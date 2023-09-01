// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "BasicAttribute.h"
#include "FPS_FuncLib.h"
#include "Component\InventoryComponent.h"
#include "Components/TimelineComponent.h"
#include "FPS_NetworkCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	STATE_BASE,
	STATE_SPRINT,
	STATE_CROUCH,
	STATE_SLIDE,
	STATE_RELORD
};

class UInventoryComponent;
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

	//** Relord Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* RelordAction;

	//** Inventory Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
    class UInputAction* Inventory_Num1Action;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* Inventory_Num2Action;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* Inventory_Num3Action;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input,meta = (AllowPrivateAccess = "true"))
	class UInputAction* Inventory_KeyGAction;
	
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

	//物品栏当前序列
	UPROPERTY(Replicated,EditAnywhere,BlueprintReadWrite,Category=Inventory,meta = (AllowPrivateAccess = "true"))
	int CurrentInventoryIndex=-1;

	//角色当前状态
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=State,meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;
	

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

	/** Called for Fire input */
	UFUNCTION(BlueprintImplementableEvent)
	void StartRelord();

	UFUNCTION(BlueprintImplementableEvent)
	void EndRelord();

	/** Called for Inventory input */
	UFUNCTION(BlueprintImplementableEvent)
	void UseInventoryOne();

	UFUNCTION(BlueprintImplementableEvent)
	void UseInventoryTwo();

	UFUNCTION(BlueprintImplementableEvent)
	void UseInventoryThree();

	UFUNCTION(BlueprintImplementableEvent)
	void DropTheWeapon();
	

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


protected:
	//引入组件
	UPROPERTY(Replicated,VisibleAnywhere,BlueprintReadOnly,Category=Component,meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

public:
	//获得组件的方法
	FORCEINLINE class UInventoryComponent* GetInventoryComponent(){ return InventoryComponent; }
	
};

