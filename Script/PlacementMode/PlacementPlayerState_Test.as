class APlacementPlayerState : APlayerState
{
    UPROPERTY(DefaultComponent)
    UPlacementPSComponent PlacementPSComponent;
    
    default bReplicates = true;

    
    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        if(this.PlayerController  == nullptr)
        {
            PlacementPSComponent.ComponentTickEnabled = false;
        }
        
    }
}