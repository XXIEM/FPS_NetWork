


class APlacementActorBase : AActor
{
    //SetDefault 
    default bReplicates = true;
 
   UPROPERTY(DefaultComponent)
   UPlacementActorComponent PlacementActorComponent;


   UFUNCTION(BlueprintOverride)
   void BeginPlay()
   {
      PlacementActorComponent.OnPlacementStateChange.BindUFunction(this,n"OnStateChange");
   }
    
    UFUNCTION(BlueprintEvent)
    private void OnStateChange(EPlacementActorStateType State, AActor InSpawner)
    {
      
    }
}