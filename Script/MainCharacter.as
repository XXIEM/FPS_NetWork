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
    float WalkSpeed = 200.0f;
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
        InitWeaponList();
        
    }

    UFUNCTION(Server)
    void InitWeaponList()
    {
        ExistGun.SetNum(3);
        
    }

    UFUNCTION(BlueprintEvent)
    void WeaponMove(){}
    UFUNCTION(BlueprintEvent)
    void AddMainUI(){}


    UFUNCTION()//初始化武器
    void InitWeaponBP(TSubclassOf<AWeaponBase>InWeapon, int Index)
    {
        if(ExistGun.Num()<=3)
        {
            // if(HasAuthority())
            // {
            //     ExistGun.Add(SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0))); 
            // }
            // else
            // {
            //     ExistGun.Add(SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0))); 
            // }
            AWeaponBase Test;
            ExistGun[Index]=SpawnActor(InWeapon,FVector(0,0,0),FRotator(0,0,0));
            
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

    UFUNCTION()//切换武器
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
    UFUNCTION(BlueprintEvent)//播放切换武器蒙太奇
    void SwitchWeaponMontageIn(){}
    UFUNCTION(BlueprintEvent)//播放切换武器蒙太奇
    void SwitchWeaponMontageOut(){}
    

    //——————————————————————————————————————重载输入映射————————————————————————————————————————————————————————

    //瞄准输入
    UFUNCTION(BlueprintOverride)
    void StartAim()
    {

        bIsAim = true;
        if(CurrentState!=ECharacterState::STATE_SPRINT && CurrentState!=ECharacterState::STATE_RELORD)
        {
            StartAimSwitchCurve();
        }
    }
    UFUNCTION(BlueprintOverride)
    void EndAim()
    {
        bIsAim = false;
        if(CurrentState!=ECharacterState::STATE_SPRINT && CurrentState!=ECharacterState::STATE_RELORD)
        {
            EndAimSwitchCurve();
        }
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
                CurrentState = ECharacterState::STATE_CROUCH;
                Crouch();
                bIsCrouch = true;
                
                
            }
            else
            {
                CurrentState = ECharacterState::STATE_BASE;
                UnCrouch();
                bIsCrouch = false;
                
                
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
        if(CurrentState!=ECharacterState::STATE_RELORD)
        {
            AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
            StartSprintOnServer();
        }
        
    }
    UFUNCTION(BlueprintOverride)
    void EndSprint()
    {
        if(CurrentState!=ECharacterState::STATE_RELORD)
        {
            AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
            EndSprintOnServer();
        }
        else if(bIsFire==true)
        {
            StartFireOnServer();
        }
        else if(bIsAim==true)
        {
            StartAim();
        }

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
        if(Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).TotalBulletNum!=0)
        {
            EndSprint();
            Cast<AWeaponBase>(ExistGun[CurrentInventoryIndex]).CallReloadMontage();
            Print("Relord!!");
        }
    }
    UFUNCTION(BlueprintOverride)
    void EndRelord()
    {
        
    }
   
    

    //————————————————————————————————————————————————————————————————————————————————————————————————————————
    //


    //服务端下蹲/滑铲输入
    UFUNCTION(Server)
    void StartCrouchOnServer()
    {
        
        //AFPS_FuncLib::SetMaxWalkspeed(this,CrouchSpeed);

    }
    UFUNCTION(Server)
    void EndCrouchOnServer()
    {
        

        
        //AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
    }


    //服务端冲刺输入
    UFUNCTION(Server)
    void StartSprintOnServer()
    {
        
        bIsCrouch = false;
        bIsSprint = true;
        CurrentState = ECharacterState::STATE_SPRINT;
        UnCrouch();
        AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
    }
    UFUNCTION(Server)
    void EndSprintOnServer()
    {
        CurrentState = ECharacterState::STATE_BASE;
        bIsSprint = false;
        AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
    }


    //服务端滑铲输入
    UFUNCTION(Server)
    void StartSlideOnServer()
    {
        CurrentState = ECharacterState::STATE_SLIDE;
        bIsSlide = true;
        AFPS_FuncLib::SetMaxCrouchspeed(this,SlideSpeed);
        Crouch();
        
    }    
    UFUNCTION(Server)
    void EndSlideOnServer()
    {
        bIsSlide = false;
        AFPS_FuncLib::SetMaxCrouchspeed(this,CrouchSpeed);
        UnCrouch();
        if(bIsSprint)
        {
            CurrentState = ECharacterState::STATE_SPRINT;
            AFPS_FuncLib::SetMaxWalkspeed(this,SprintSpeed);
        }
        else
        {
            CurrentState = ECharacterState::STATE_BASE;
            AFPS_FuncLib::SetMaxWalkspeed(this,WalkSpeed);
        }
    }    

   

    //服务端发射输入
    UFUNCTION(NetMulticast)
    void StartFireOnServer()
    {
        bIsFire = true;
        if(CurrentInventoryIndex != -1 && CurrentState!=ECharacterState::STATE_SPRINT && CurrentState!=ECharacterState::STATE_RELORD)
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

        SwitchWeaponMontageIn();
        // CurrentInventoryIndex = 2;
        // // UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        // // if(InWeapon!=nullptr)
        // // {
        // //     SetWeaponBP(InWeapon);
        // //     LastWeapon = InWeapon;
        // // }
        // SwitchWeaponBP(CurrentInventoryIndex);
        // SwitchWeaponMontageOut();
    }

    

}