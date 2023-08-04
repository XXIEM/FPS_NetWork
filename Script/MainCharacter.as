class AMainCharacter:AFPS_NetworkCharacter
{
    UPROPERTY(DefaultComponent,Attach=CharacterMesh0,AttachSocket=head)
    UCineCameraComponent Camera;
    default Camera.bUsePawnControlRotation = true;



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

    UPROPERTY()
    UClass Weapon_AR4;

    //绘制后的枪
    UPROPERTY()
    AActor SpawnGun = nullptr;

    UPROPERTY()
    UClass LastWeapon;//绘制的上一个枪

    //绘制后的枪骨骼的trans
    UPROPERTY()
    FTransform WeaponBoneTrans;

    //自身变量
    float WalkSpeed = 300.0f;
    float CrouchSpeed = 150.0f;
    float SprintSpeed = 500.0f;
    float SlideSpeed = 400.0f;

    


    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        //SetWeaponBP();

        if(SpawnGun!=nullptr)
        {
        Cast<AWeaponBase>(SpawnGun).MainCharacter=this;
        }
        WeaponMove();

        
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
        CurrentInventoryIndex = 0;
        
        UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        if(InWeapon!=nullptr)
        {
            SetWeaponBP(InWeapon);
            LastWeapon = InWeapon;
        }
        
       
    }
    UFUNCTION(BlueprintOverride)
    void UseInventoryTwo()//键位2
    {
        CurrentInventoryIndex = 1;
        UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        if(InWeapon!=nullptr)
        {
            SetWeaponBP(InWeapon);
            LastWeapon = InWeapon;
        }
        
    }
    UFUNCTION(BlueprintOverride)
    void UseInventoryThree()//键位3
    {
        CurrentInventoryIndex = 2;
        UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
        if(InWeapon!=nullptr)
        {
            SetWeaponBP(InWeapon);
            LastWeapon = InWeapon;
        }
    }
    UFUNCTION(BlueprintOverride)
    void DropTheWeapon()
    {
        if(SpawnGun!=nullptr)
        {
            UClass DropWeaponBP = this.InventoryComponent.Get_WeaponPickUp(CurrentInventoryIndex);
            AActor DropWeapon = SpawnActor(DropWeaponBP,GetActorLocation()+GetActorForwardVector()*130,FRotator(0,0,0));
            

            this.InventoryComponent.RemoveInventoryItem(CurrentInventoryIndex);
            SpawnGun.DestroyActor();
            SpawnGun = nullptr;
            
            
            
            CurrentInventoryIndex = this.InventoryComponent.FindNextExistWeapon();
            if(CurrentInventoryIndex != -1)
            {
                UClass InWeapon = this.InventoryComponent.Get_WeaponBP(CurrentInventoryIndex);
                if(InWeapon!=nullptr)
                {
                    SetWeaponBP(InWeapon);
                }
            }
        }
        
       

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
        if(SpawnGun!=nullptr)
        {
            Cast<AWeaponBase>(SpawnGun).Fire(this);
        }
    }
    UFUNCTION(NetMulticast)
    void EndFireOnServer()
    {
        bIsFire = false;
        if(SpawnGun!=nullptr)
        {
            Cast<AWeaponBase>(SpawnGun).StopFire();
        }
    }


    

}