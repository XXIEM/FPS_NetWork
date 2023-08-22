class AMainCharacter:AFPS_NetworkCharacter
{


    UPROPERTY(DefaultComponent,Attach=CharacterMesh0,AttachSocket = head)
    UCineCameraComponent Camera;
    //default Camera.bUsePawnControlRotation = true;



    UPROPERTY(Replicated)
    bool bIsAim = false;//是否瞄准

    UPROPERTY(Replicated)
    bool bIsCrouch = false;//是否蹲伏or滑铲

    UPROPERTY(Replicated)
    bool bIsSprint = false;//是否冲刺

    UPROPERTY(Replicated)
    bool bIsSlide = false;//是否滑铲

    UPROPERTY(Replicated)
    bool bIsFire = false;//是否射击

    UPROPERTY(Replicated)
    bool bIsReload = false;//是否换弹

    UPROPERTY()
    UClass Weapon_AR4;

    //绘制后的枪
    UPROPERTY()
    AActor SpawnGun = nullptr;

    UPROPERTY(Replicated)
    TArray<AActor> ExistGun;

    UPROPERTY()
    UClass LastWeapon;//绘制的上一个枪

    //绘制后的枪骨骼的trans
    UPROPERTY()
    FTransform WeaponBoneTrans;

    //Relord的UI变量
    UPROPERTY()
    UUserWidget UI_Relord;

    //自身变量
    float WalkSpeed = 300.0f;
    float CrouchSpeed = 150.0f;
    float SprintSpeed = 500.0f;
    float SlideSpeed = 400.0f;

    


    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        //SetWeaponBP();
      
        // if(SpawnGun!=nullptr)
        // {
        // Cast<AWeaponBase>(SpawnGun).MainCharacter=this;
        // }
        WeaponMove();
        AddMainUI();
        //InitWeaponList();
        
    }

    UFUNCTION(Server)
    void InitWeaponList()
    {
        ExistGun.SetNum(3);
        
    }

    //绘制枪的蓝图
    UFUNCTION()
    void SetWeaponBP(UClass InWeapon)
    {

        if(LastWeapon!=InWeapon)
        {
            if(SpawnGun==nullptr)
            {
                SpawnGun = SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0));
                SpawnGun.ActorScale3D=FVector(1,1,1);
                SpawnGun.AttachToComponent(Mesh,n"VB Weapon",EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);
                //WeaponBoneTrans = Cast<AWeaponBase>(SpawnGun).SkeletalMesh.GetSocketTransform(n"AimPoint",ERelativeTransformSpace::RTS_Actor);
                WeaponBoneTrans = Cast<AWeaponBase>(SpawnGun).AimPointTest.GetRelativeTransform();
            }
            else
            {
                SpawnGun.DestroyActor();
                SpawnGun = nullptr;
                SpawnGun = SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0));
                SpawnGun.ActorScale3D=FVector(1,1,1);
                SpawnGun.AttachToComponent(Mesh,n"VB Weapon",EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);
                //WeaponBoneTrans = Cast<AWeaponBase>(SpawnGun).SkeletalMesh.GetSocketTransform(n"AimPoint",ERelativeTransformSpace::RTS_Actor);
                WeaponBoneTrans = Cast<AWeaponBase>(SpawnGun).AimPointTest.GetRelativeTransform();
            }
        }
    }

    UFUNCTION(BlueprintEvent)
    void WeaponMove(){}
    UFUNCTION(BlueprintEvent)
    void AddMainUI(){}

    UFUNCTION(NetMulticast)
    void InitWeaponBP(UClass InWeapon)
    {
        if(ExistGun.Num()<=3)
        {
            if(HasAuthority())
            {
                ExistGun.Add(SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0))); 
            }
            else
            {
                ExistGun.Add(SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0))); 
            }
        }
  
        ExistGun[CurrentInventoryIndex].ActorScale3D=FVector(1,1,1);
        ExistGun[CurrentInventoryIndex].AttachToComponent(Mesh,n"VB Weapon",EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);
        WeaponBoneTrans = Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).AimPointTest.GetRelativeTransform();
        Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).MainCharacter = this;
        Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).CallUIReloadUpdate();//更新UI的弹药量

        //ExistGun[i].DetachFromActor(EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative);
        //ExistGun[i].SetActorLocation(FVector(0,0,-200));
        for(auto i = 0 ;i<ExistGun.Num();i++)
        {
            if(i!=CurrentInventoryIndex)
            {
                if(ExistGun[i]!=nullptr)
                {
                    ExistGun[i].SetActorHiddenInGame(true);
                }
            }
            
        }
        
        
    }

    UFUNCTION()
    void SwitchWeaponBP(int Index)
    {
        for(int i = 0;i<ExistGun.Num();i++)
        {
            if(Index!=i)
            {
                if(ExistGun[i]!=nullptr)
                {
                    ExistGun[i].SetActorHiddenInGame(true);
                }
            }
            else
            {
                if(ExistGun[i]!=nullptr)
                {
                    ExistGun[i].SetActorHiddenInGame(false);
                    WeaponBoneTrans = Cast<AWeaponBase>(ExistGun[i]).AimPointTest.GetRelativeTransform();
                    Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).CallUIReloadUpdate();//更新UI的弹药量
                }
            }
            //Print(ExistGun[i].GetActorLabel());
        }
        

    }

    

    //——————————————————————————————————————重载输入映射————————————————————————————————————————————————————————

    //瞄准输入
    UFUNCTION(BlueprintOverride)
    void StartAim()
    {
        StartAimOnServer();
        StartAimSwitchCurve();
        
    }
    UFUNCTION(BlueprintOverride)
    void EndAim()
    {
        EndAimOnServer();
        EndAimSwitchCurve();
    }
    UFUNCTION(BlueprintEvent)
    void StartAimSwitchCurve(){}
    UFUNCTION(BlueprintEvent)
    void EndAimSwitchCurve(){}
    


    
    //蹲伏or滑铲输入
    UFUNCTION(BlueprintOverride)
    void StartCrouchSlide()
    {  
        if(bIsSprint==false)
        {
            if(!bIsCrouch)//本地执行逻辑
            {
                AFPS_FuncLib::SetMaxWalkspeed(this,CrouchSpeed);
                StartCrouchOnServer();
            }
            else
            {
                AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
                EndCrouchOnServer();
            }
        }
        else
        {
            if(!bIsSlide)
            {
                AFPS_FuncLib::SetMaxWalkspeed(this,SlideSpeed);
                StartSlideOnServer();
            }
        }
        

    }

    
    //冲刺输入
    UFUNCTION(BlueprintOverride)
    void StartSprint()
    {
        AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
        StartSprintOnServer();
        
    }
    UFUNCTION(BlueprintOverride)
    void EndSprint()
    {
        AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
        EndSprintOnServer();
    }


    //发射输入
    UFUNCTION(BlueprintOverride)
    void StartFire()
    {
        StartFireOnServer();
    }
    UFUNCTION(BlueprintOverride)
    void EndFire()
    {
        EndFireOnServer();
    }

    //物品栏输入
    UFUNCTION(BlueprintOverride)
    void UseInventoryOne()//键位1
    {
        
        UseInventoryOneOnServer();
        //SwitchWeaponBP(CurrentInventoryIndex);
    }
    UFUNCTION(BlueprintOverride)
    void UseInventoryTwo()//键位2
    {
        UseInventoryTwoOnServer();
        //SwitchWeaponBP(CurrentInventoryIndex);
    }
    UFUNCTION(BlueprintOverride)
    void UseInventoryThree()//键位3
    {
        UseInventoryThreeOnServer();
        
    }
    UFUNCTION(BlueprintOverride)
    void DropTheWeapon()
    {

    }

    UFUNCTION(BlueprintOverride)
    void StartRelord()
    {
        //Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).CallUIReloadUpdate();
        Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).CallReloadMontage();
        Print("Relord!!");
    }
    UFUNCTION(BlueprintOverride)
    void EndRelord()
    {
        
    }
   
    

    //————————————————————————————————————————————————————————————————————————————————————————————————————————

    //———————————————————————————————————————网络同步输入映射——————————————————————————————————————————————————
    //服务端瞄准输入
    UFUNCTION(Server)
    void StartAimOnServer()
    {
            bIsAim = true;
    }
    UFUNCTION(Server)
    void EndAimOnServer()
    {
            bIsAim = false;
    }


    //服务端下蹲/滑铲输入
    UFUNCTION(Server)
    void StartCrouchOnServer()
    {
     
        bIsCrouch = true;
        AFPS_FuncLib::SetMaxWalkspeed(this,CrouchSpeed);

    }
    UFUNCTION(Server)
    void EndCrouchOnServer()
    {
        bIsCrouch = false;
        AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
    }


    //服务端冲刺输入
    UFUNCTION(Server)
    void StartSprintOnServer()
    {
        bIsCrouch = false;
        bIsSprint = true;
        AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
    }
    UFUNCTION(Server)
    void EndSprintOnServer()
    {
        bIsSprint = false;
        AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
    }


    //服务端滑铲输入
    UFUNCTION(Server)
    void StartSlideOnServer()
    {
        bIsSlide = true;
        AFPS_FuncLib::SetMaxWalkspeed(this,SlideSpeed);
    }    
    UFUNCTION(Server)
    void EndSlideOnServer()
    {
        bIsSlide = false;
        if(bIsSprint)
        {
            AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
        }
        else
        {
            AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
        }
        
    }    

    //服务端发射输入
    UFUNCTION(NetMulticast)
    void StartFireOnServer()
    {
        bIsFire = true;
        if(CurrentInventoryIndex != -1)
        {
            if(ExistGun[CurrentInventoryIndex]!=nullptr)
            {
                Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).Fire(this);
            }
        }
    }
    UFUNCTION(NetMulticast)
    void EndFireOnServer()
    {
        bIsFire = false;
        if(CurrentInventoryIndex != -1)
        {
            if(ExistGun[CurrentInventoryIndex]!=nullptr)
            {
                Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).StopFire();
            }
        }
    }

    //服务端物品栏输入
    UFUNCTION(Server)
    void UseInventoryOneOnServer()
    {
        CurrentInventoryIndex = 0;
        // UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        // if(InWeapon!=nullptr)
        // {
        //     SetWeaponBP(InWeapon);
        //     LastWeapon = InWeapon;
        // }
        SwitchWeaponBP(CurrentInventoryIndex);
    }

    UFUNCTION(Server)
    void UseInventoryTwoOnServer()
    {
        CurrentInventoryIndex = 1;
        // UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        // if(InWeapon!=nullptr)
        // {
        //     SetWeaponBP(InWeapon);
        //     LastWeapon = InWeapon;
        // }
        SwitchWeaponBP(CurrentInventoryIndex);
    }

    UFUNCTION(Server)
    void UseInventoryThreeOnServer()
    {
        CurrentInventoryIndex = 2;
        // UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        // if(InWeapon!=nullptr)
        // {
        //     SetWeaponBP(InWeapon);
        //     LastWeapon = InWeapon;
        // }
        SwitchWeaponBP(CurrentInventoryIndex);
    }

    

}