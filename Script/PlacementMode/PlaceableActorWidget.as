class UPlacementActorWidget : UUserWidget
{
    UPROPERTY(BindWidget,ExposeOnSpawn)
    UImage Image;  
    UPROPERTY(BindWidget,ExposeOnSpawn)
    UTextBlock NumText;

    UPROPERTY(BindWidget,ExposeOnSpawn)
    UTextBlock NameText;

    UPROPERTY(NotVisible)
    UPlacementActorComponent PlacementActorComponent;

    UPROPERTY(NotVisible)
    UPlacementPSComponent PlacementPSComponent;

    //与此Widget绑定的Actor信息
    UPROPERTY(ExposeOnSpawn,EditAnywhere)
    TSubclassOf<AActor> ActorClass;

    
    UFUNCTION(BlueprintOverride)
    FEventReply OnMouseButtonDown(FGeometry MyGeometry, FPointerEvent MouseEvent)
    {
        auto OutEvent = Widget::DetectDragIfPressed(MouseEvent,this,FKey(EKeys::LeftMouseButton));

        return OutEvent;
    }

    UFUNCTION(BlueprintOverride)
    void OnDragDetected(FGeometry MyGeometry, FPointerEvent PointerEvent,UDragDropOperation& Operation)
    {
        Operation = Cast<UDragDropOperation>(NewObject(this,UDragDropOperation::StaticClass()));
        if(ActorClass.IsValid()&&PlacementActorComponent!=nullptr)
        {
            PlacementPSComponent.SpawnActor_Server(ActorClass);
            
        }
    }

    UFUNCTION(BlueprintOverride)
    void OnDragCancelled(FPointerEvent PointerEvent, UDragDropOperation Operation)
    {
        
        #if EDITOR
        Print(f"{this.GetName()}::OnDropCancelled");
        #endif
        PlacementPSComponent.PlaceFinish_Server();

    }


    UFUNCTION(BlueprintOverride)
    void Construct()
    {
        if(ActorClass.IsValid())
        {
            PlacementActorComponent = UPlacementActorComponent::Get(Cast<AActor>(ActorClass.Get().DefaultObject));
        }
        auto PC = Gameplay::GetPlayerController(0);
        auto PS =  PC.PlayerState;
        if(PS != nullptr)
        {
            PlacementPSComponent = UPlacementPSComponent::Get(PS);
        }
        if(PlacementActorComponent !=nullptr)
        {
            Image.SetBrushFromTexture(PlacementActorComponent.UITexture);
            NameText.SetText(FText::FromString(f"{PlacementActorComponent.PlacementActorName}"));      
        }
    }

    UFUNCTION(BlueprintOverride)
    void Tick(FGeometry MyGeometry, float InDeltaTime)
    {
        UpdateText();
    }


    UFUNCTION()
    void UpdateText()
    {
        if( PlacementActorComponent !=nullptr && PlacementPSComponent != nullptr)
        {
            auto Index = PlacementPSComponent.FindIndexInPlacementActors(PlacementActorComponent.PlacementActorName);

            if(Index!=-1)
            {
                NumText.SetText(FText::FromString(f"{PlacementPSComponent.PlacementActors.Items[Index].Num}"));
            }
            
        }
    }
       
          
    
}