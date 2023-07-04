// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_NetworkCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AFPS_NetworkCharacter

AFPS_NetworkCharacter::AFPS_NetworkCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//初始化AS与ASC
	BAS=CreateDefaultSubobject<UBasicAttribute>(TEXT("BasicAS"));
	AbilityComp=CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComp"));


}


void AFPS_NetworkCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//初始化能力数组
	if(nullptr!=AbilityComp)
	{
		if(HasAuthority()&& StartupAbilitys.Num()>0)
		{
			for(auto i=0; i<StartupAbilitys.Num();i++)
			{
				if(StartupAbilitys[i]==nullptr)
				{
					continue;
				}
				AbilityComp->GiveAbility(FGameplayAbilitySpec(StartupAbilitys[i].GetDefaultObject(),1,0));
			}
		}
		AbilityComp->InitAbilityActorInfo(this,this);
	}


}



//////////////////////////////////////////////////////////////////////////
// Input

void AFPS_NetworkCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPS_NetworkCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPS_NetworkCharacter::Look);

		//Aim
		EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Started,this,&AFPS_NetworkCharacter::StartAim);
		EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Canceled,this,&AFPS_NetworkCharacter::EndAim);

		// Crouch/Slide
		EnhancedInputComponent->BindAction(CrouchSLideAction,ETriggerEvent::Started,this,&AFPS_NetworkCharacter::StartCrouchSlide);
		EnhancedInputComponent->BindAction(CrouchSLideAction,ETriggerEvent::Canceled,this,&AFPS_NetworkCharacter::EndcrouchSlide);

		//Sprint
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Started,this,&AFPS_NetworkCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Canceled,this,&AFPS_NetworkCharacter::EndSprint);

		//Fire
		EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Started,this,&AFPS_NetworkCharacter::StartFire);
		EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Canceled,this,&AFPS_NetworkCharacter::EndFire);
	}

}

UAbilitySystemComponent* AFPS_NetworkCharacter::GetAbilitySystemComponent() const
{
	return AbilityComp;
}

void AFPS_NetworkCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFPS_NetworkCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




