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

    UPROPERTY(Replicated)
    bool bIsFire = false;//是否射击

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

    
    //瞄准时间轴插值
    UTimelineComponent AimTimeline;
    FOnTimelineFloat OnAimTimelineTickCallback;
    FOnTimelineEvent OnAimTimelineFinishedCallback; 
    UPROPERTY(Category = TimelineCurve)
    UCurveFloat AimCurve;//时间轴曲线





    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        SetWeaponBP();

        if(SpawnGun!=nullptr)
        {
        Cast<AWeapon_AR4>(SpawnGun).MainCharacter=this;
        }

        
        //绑定Aim时间轴的timeline回调
        OnAimTimelineTickCallback.BindUFunction(this,n"AimTimelineTickCallBack");
        AimTimeline.AddInterpFloat(AimCurve,OnAimTimelineTickCallback);

        OnAimTimelineFinishedCallback.BindUFunction(this,n"AimTimelineFinishedCallback");
        AimTimeline.SetTimelineFinishedFunc(OnAimTimelineFinishedCallback);
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
        StartAimOnServer();
  
        //AimTimeline.Play();
     
        
    }
    UFUNCTION(BlueprintOverride)
    void EndAim()
    {
        EndAimOnServer();
    }
    UFUNCTION()
    void AimTimelineTickCallBack(float32 value)
    {
        float AlphaVal = AimCurve.GetFloatValue(value);
        float LerpRet = Math::Lerp(0.f,-30.f,AlphaVal);
        float Fov = 100.f + LerpRet;
        Camera.SetFieldOfView(Fov);
        
    }
    UFUNCTION()
    void AimTimelineFinishedCallback()
    {

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
    UFUNCTION()
    void StartFireOnServer()
    {
        bIsFire = true;
        Cast<AWeapon_AR4>(SpawnGun).Fire();
    }
    UFUNCTION()
    void EndFireOnServer()
    {
        bIsFire = false;
        Cast<AWeapon_AR4>(SpawnGun).StopFire();
    }


    

}