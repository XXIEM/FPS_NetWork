class AMainCharacter:AFPS_NetworkCharacter
{
    UPROPERTY(DefaultComponent,Attach=CharacterMesh0,AttachSocket=head)
    UCameraComponent Camera;
    default Camera.bUsePawnControlRotation = true;

    UPROPERTY(Replicated)
    bool bIsAim = false;//是否瞄准

    UPROPERTY(Replicated)
    bool bIsCrouch = false;//是否蹲伏or滑铲

    UPROPERTY(Replicated)
    bool bIsSprint = false;//是否冲刺

    UPROPERTY(Replicated)
    bool bIsSlide = false;//是否滑铲

    UPROPERTY()
    UClass Weapon_AR4;

    //绘制后的枪
    UPROPERTY()
    AActor SpawnGun;

    //自身变量
    float WalkSpeed = 300.0f;
    float CrouchSpeed = 150.0f;
    float SprintSpeed = 600.0f;
    float SlideSpeed = 450.0f;

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        SetWeaponBP();

        if(SpawnGun!=nullptr)
        {
        Cast<AWeapon_AR4>(SpawnGun).MainCharacter=this;
        }
        
    }
    //初始绘制枪的蓝图
    UFUNCTION(BlueprintEvent)
    void SetWeaponBP()
    {
        SpawnGun = SpawnActor(Weapon_AR4,FVector(0,0,0),FRotator(0,0,0));
        SpawnGun.ActorScale3D=FVector(1,1,1);
        SpawnGun.AttachToComponent(Mesh,n"Weapon_Attach",EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,true);
        
        
    }

    //——————————————————————————————————————重载输入映射————————————————————————————————————————————————————————

    //瞄准输入
    UFUNCTION(BlueprintOverride)
    void StartAim()
    {
        AimOnServer();
    }
    UFUNCTION(BlueprintOverride)
    void EndAim()
    {
        AimOnServer();
    }

    
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

    

    //————————————————————————————————————————————————————————————————————————————————————————————————————————

    //———————————————————————————————————————网络同步输入映射——————————————————————————————————————————————————
    //服务端瞄准输入
    UFUNCTION(Server)
    void AimOnServer()
    {
        if(!bIsAim)
        {
            bIsAim = true;
        }
        else
        {
            bIsAim = false;
        }
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


    

}