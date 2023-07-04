
class UPlacementPSComponent : UPlacementPSComponentBase
{


    //存储当前正在放置的Actor
    UPROPERTY(NotVisible,Replicated)
    AActor SpawnedActor;

    
    private FVector MousePosition_WS;
    private FVector MouseDirection_WS;

    default ComponentTickEnabled = true;
    default bReplicates = true;
   
 


    /**
     * @description: 判断Actor是否可以放置
     * @param InActorName 需要判断的Actor的名字
     * @return 是否可以放置
     */    
    UFUNCTION(BlueprintPure)
    protected bool CanPlace(UClass InActor)
    {
        auto PlacementActorComponent = UPlacementActorComponent::Get(Cast<AActor>(InActor.GetDefaultObject()));
        if(PlacementActorComponent == nullptr)
        {
            Print("PlacementActorComponent == nullptr");
            return false;
        }
        uint8 Value = 0;
        auto Index = this.FindIndexInPlacementActors(PlacementActorComponent.PlacementActorName);
        if(Index!=-1)
        { 
            Value = PlacementActors.Items[Index].Num;
            if(Value > 0) return true;
            else 
            {
                Print("Value < 0");
                return false;
            }

        }
        else
        {
            Print("NotFoundKey");
            return false;
        }
        
    }

    /**
     * @description: 将Actor加入PlacementActorMap，让Actor可放置的数量增加，如果已经存在则在此基础上增加数量，不存在则直接添加。
     * @param InActor Actor的类型
     * @param InNum 需要添加的数量
     * @return 是否加入成功
     */    
    UFUNCTION(Server)
    void AddPlacementActor_Server(UClass InActor,uint8 InNum  = 1)
    {
        UPlacementActorComponent PlacementActorComponent;
        GetPlacementActorComponent(InActor,PlacementActorComponent);
        if(PlacementActorComponent == nullptr)
        {
            return ;
        }
        else
        {
            auto Index = this.FindIndexInPlacementActors(PlacementActorComponent.PlacementActorName);
            uint8 Value; 
            if(Index!= -1) 
            {
                PlacementActors.Items[Index].Num += InNum;
                Print(f"{PlacementActorComponent.PlacementActorName}Remain{PlacementActors.Items[Index].Num}");
                this.MarkItemDirty(PlacementActors.Items[Index]);
            } 
            else 
            {
                FPlacementActorInfo TempInfo;
                TempInfo.ActorName = PlacementActorComponent.PlacementActorName;
                TempInfo.Num = InNum;
                PlacementActors.Items.Add(TempInfo);
                this.MarkItemDirty(PlacementActors.Items.Last());
                Print(f"{PlacementActorComponent.PlacementActorName}Remain{PlacementActors.Items.Last().Num}");
            }
            return;

        }
    }
    /**
     * @description: 将Actor从PlacementActorMap中移除
     * @param InActor Actor的类型
     * @param InNum 需要移除的数量
     * @return 是否移除成功
     */    
    UFUNCTION(Server)
    void RemovePlacementActor_Server(UClass InActor,uint8 InNum = 1 )
    {
        UPlacementActorComponent PlacementActorComponent;
        auto HasComponent = GetPlacementActorComponent(InActor,PlacementActorComponent);
        if(!HasComponent)
        {
            return ;
        }
        uint8 Value;
        auto Index = this.FindIndexInPlacementActors(PlacementActorComponent.PlacementActorName);
        if(Index  == -1)
        {
            return;
        }

        if(PlacementActors.Items[Index].Num == 0)
        {
            this.RemoveItemFromPlacementActors(Index);
            return;
        }

        if(InNum > PlacementActors.Items[Index].Num )
        {
            Print(f"{this.GetName()}ToManyNum");
            return ;
        }
        PlacementActors.Items[Index].Num -= InNum;
        this.MarkItemDirty(PlacementActors.Items[Index]);
        Print(f"{PlacementActorComponent.PlacementActorName}Remain{PlacementActors.Items[Index].Num}");
        return;
    }
    


    /**
     * @description: 在服务器生成一个Actor 
     * @param InActorClass 要生成Actor的类型
     * @param InTransform 生成Actor的Transfrom信息
     * @return 生成Actor的引用
     */    
    UFUNCTION(Server)
    void SpawnActor_Server(TSubclassOf<AActor> InActorClass,FTransform InTransform = FTransform::Identity)
    {
        AActor OutActor = nullptr;
        if(CanPlace(InActorClass.Get()))
        {
            OutActor = SpawnActor(InActorClass.Get(),InTransform.Location,InTransform.Rotator());
            auto TempComponent  = UPlacementActorComponent::Get(OutActor);
            TempComponent.ChangeState_Server(EPlacementActorStateType::UnPlace,Cast<APlayerState>(this.Owner).PlayerController);
            RemovePlacementActor_Server(InActorClass.Get());
            //OutActor.SetOwner(Cast<APlayerState>(this.Owner).PlayerController);
        }
        this.SpawnedActor =  OutActor;
    }

    /**
     * @description: 
     * @param 
     * @return 
     */    
    UFUNCTION(Server)
    void PlaceFinish_Server()
    {
        if(SpawnedActor != nullptr)
        {
            auto TempComponent  = UPlacementActorComponent::Get(SpawnedActor);
            TempComponent.ChangeState_Server(EPlacementActorStateType::Place,Cast<APlayerState>(this.Owner).PlayerController);
            SpawnedActor = nullptr;
        }
    }

  



    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        auto PC = Cast<APlayerState>(this.Owner).PlayerController;
        //Trace to update spawned actor location
        if(PC!=nullptr && PC.IsLocalController())
        {
            FVector2D MousePosition = WidgetLayout::GetMousePositionOnViewport()*WidgetLayout::ViewportScale;
            Gameplay::DeprojectScreenToWorld(Gameplay::GetPlayerController(0),MousePosition,MousePosition_WS,MouseDirection_WS);
            if(SpawnedActor != nullptr)
            { 
                FHitResult HitResult;
                TArray<AActor> ActorToIgnore;
                ActorToIgnore.Add(Gameplay::GetPlayerPawn(0));
                auto bIsHit  = System::LineTraceSingle(MousePosition_WS,MousePosition_WS + MouseDirection_WS *2000,ETraceTypeQuery::Camera,false,ActorToIgnore,EDrawDebugTrace::ForOneFrame,HitResult,true);
                if(bIsHit)
                {
                    UpdateSpawnedActorTransform_Server(FTransform(HitResult.Location));
                }
                
            }
        }
        
    }


     /**
     * @description: 判断Actor是否拥有PlacementActorComponent组件
     * @param InActor Actor类型
     * @return 是否找到组件
     */ 
    UFUNCTION(BlueprintPure)
    protected  bool GetPlacementActorComponent(UClass InActor,UPlacementActorComponent&out InComponent)
    {
        InComponent = UPlacementActorComponent::Get(Cast<AActor>(InActor.GetDefaultObject()));
        if(InComponent == nullptr)
        {
            return false;
        }
        return true;
    }


    UFUNCTION(Server)        
    void UpdateSpawnedActorTransform_Server(FTransform InTransform)
    {
        if(SpawnedActor == nullptr) return;
       
        //TODO:UpdateTransform
        SpawnedActor.SetActorTransform(InTransform);        
    }
    
}