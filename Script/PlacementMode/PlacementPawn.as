

class APlacementPawn : APawn
{
    UPROPERTY(NotVisible)
    APlayerState PS;
    UPROPERTY(NotVisible)
    AActor ActorSpawned;


    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        if(ActorSpawned != nullptr)
        {
            FVector MousePosition;
            FVector MouseDirection;
            GetMousePositionOnWorld(MousePosition,MouseDirection);
            //System::LineTraceSingle()
        }
    }

    UFUNCTION(BlueprintOverride)
    void ConstructionScript()
    {
        PS = Cast<APlacementPlayerState>(Gameplay::GetPlayerState(0));
    }

    UFUNCTION(Server)
    void SpawnPlacementActor(TSubclassOf<APlacementActorBase> SpawnActorType,AActor InOwner)
    {
        ActorSpawned = Cast<APlacementActorBase>(SpawnActor(SpawnActorType));
        ActorSpawned.SetOwner(InOwner);        
    }
    
    
    UFUNCTION()
    void GetMousePositionOnWorld(FVector&out MousePosition_WS,FVector&out MouseDirection_WS)
    {
        
        FVector2D MousePosition = WidgetLayout::GetMousePositionOnViewport()*WidgetLayout::ViewportScale;
        Gameplay::DeprojectScreenToWorld(Cast<APlayerController>(this.GetController()), MousePosition,MousePosition_WS,MouseDirection_WS);
    }
}