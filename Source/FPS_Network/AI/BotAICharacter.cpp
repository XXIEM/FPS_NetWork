// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAICharacter.h"
#include "AIController.h"
#include "BotAIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABotAICharacter::ABotAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	// AttributeComp = CreateDefaultSubobject<UBasicAttribute>("AttributeComp");

	// ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	// Ensures we receive a controlled when spawned in the level by our gamemode
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Enabled on mesh to react to incoming projectiles
	GetMesh()->SetGenerateOverlapEvents(true);

	TimeToHitParamName = "TimeToHit";
	TargetActorKey = "TargetActor";
}

void ABotAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorKey, NewTarget);
	}
}

AActor* ABotAICharacter::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AFPS_NetworkCharacter>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey));
	}

	return nullptr;
}

void ABotAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAICharacter::OnPawnSeen);
	// AttributeComp->OnHealthChanged.AddDynamic(this, &ABotAICharacter::OnHealthChanged);
}

void ABotAICharacter::OnHealthChanged(AActor* InstigatorActor, UBasicAttribute* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		// if (ActiveHealthBar == nullptr)
		// {
		// 	ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		// 	if (ActiveHealthBar)
		// 	{
		// 		ActiveHealthBar->AttachedActor = this;
		// 		ActiveHealthBar->AddToViewport();
		// 	}
		// }

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		// Died
		if (NewHealth <= 0.0f)
		{
			// stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			// ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			// set lifespan
			SetLifeSpan(10.0f);
		}
	}
}

void ABotAICharacter::OnPawnSeen(APawn* Pawn)
{
	// Ignore if target already set
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		MulticastPawnSeen();
	}
	//DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 0.5f, true);
}

void ABotAICharacter::MulticastPawnSeen_Implementation()
{
	// USWorldUserWidget* NewWidget = CreateWidget<USWorldUserWidget>(GetWorld(), SpottedWidgetClass);
	// if (NewWidget)
	// {
	// 	NewWidget->AttachedActor = this;
	// 	// Index of 10 (or anything higher than default of 0) places this on top of any other widget.
	// 	// May end up behind the minion health bar otherwise.
	// 	NewWidget->AddToViewport(10);
	// }BlackboardComponent.cpp
}
