// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyNodeInfoComponent.h"

#include "UI/MainHUD.h"
#include "UI/UI_StickyNotePannel.h"




// Sets default values for this component's properties
UStickyNodeInfoComponent::UStickyNodeInfoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStickyNodeInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	

	
}


// Called every frame
void UStickyNodeInfoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStickyNodeInfoComponent::InvokeMultiDynamicDelegate()
{
	
	UUI_StickyNotePannel* StickyNotePannelInstance = Cast<AMainHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->StickyNotePannel;
	FStickyNoteEvent& DynamicEvent =StickyNotePannelInstance->AddMultiDynamicDelegate();
	DynamicEvent.Broadcast(StickyNodeInfo);

}

void UStickyNodeInfoComponent::SetStickyNote(FStickyNodeInfo StickyNodeInfoIns)
{	
	StickyNodeInfo = StickyNodeInfoIns;	
}


