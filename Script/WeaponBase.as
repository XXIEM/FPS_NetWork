class AWeaponBase:AFPS_WeaponBase
{

    UPROPERTY(DefaultComponent)
    USceneComponent Scene;

    UPROPERTY(DefaultComponent,Attach = Scene)
    USkeletalMeshComponent SkeletalMesh;

    UPROPERTY(DefaultComponent,Attach = SkeletalMesh)
    USceneComponent AimPointTest;

    //UPROPERTY(DefaultComponent,Attach = SkeletalMesh)
    //USphereComponent Sphere;
    
    UPROPERTY()
    UClass Bullet;

    FTimerHandle ShootHandle;

    UPROPERTY(Replicated)
    AMainCharacter MainCharacter;

    //---------后坐力部分------------------
    UPROPERTY()
    int CurrentShootTimes = -1;

    UPROPERTY()
    float MaxRecoilY=0;//Y轴总后坐力上升距离

        UPROPERTY()
    float MaxRecoilX=0;//X轴总后坐力平移距离


    UPROPERTY()
    float UpOneTime;//单次上升的后坐力距离

    UPROPERTY()
    float LROneTime;//单次平移的后坐力距离

    UPROPERTY()
    float DropAvoidOffsetY;//回落修正Y

    UPROPERTY()
    float DropAvoidOffsetX;//回落修正X


    //---------武器动画部分-------------
      //人物骨骼武器动画
        //人物待机
        UPROPERTY()
        UAnimSequence CharacterWeaponStandby;

        //人物空仓换弹
        UPROPERTY()
        UAnimSequence CharacterEmptyReload;

        //人物非空仓换弹
        UPROPERTY()
        UAnimSequence CharacterNorEmptyReload;

        //人物武器检查
        UPROPERTY()
        UAnimSequence CharacterWeaponCheck;
    
        //人物装备动画
        UPROPERTY()
        UAnimSequence CharacterArmmedWeapon;

        //人物解除装备动画
        UPROPERTY()
        UAnimSequence CharacterUnArmmedWeapon;

      //武器骨骼武器动画
        //武器空仓检查
        UPROPERTY()
        UAnimSequence WeaponEmptyCheck;

        //武器非空仓检查
        UPROPERTY()
        UAnimSequence WeaponNorEmptyCheck;

        //武器空仓换弹
        UPROPERTY()
        UAnimSequence WeaponEmptyReload;

        //武器空仓检查
        UPROPERTY()
        UAnimSequence WeaponNorEmptyReload;

        //武器非空仓开火
        UPROPERTY()
        UAnimSequence WeaponNorEmptyFire;

        //武器空仓开火
        UPROPERTY()
        UAnimSequence WeaponEmptyFire;




    UFUNCTION(BlueprintEvent)
    void AddRecoil(){}

    UFUNCTION(BlueprintEvent)
    void RecoilDown(){}


    UFUNCTION(BlueprintEvent)
    void RecoilCameraShake(){}

    UFUNCTION(BlueprintEvent)
    void RecoilHalfway(){}

    UFUNCTION(BlueprintEvent)
    void StopUp(){}
    //------------------------------------

    //--------------换弹部分--------------
    UPROPERTY()
    int CurrentBulletNum;

    UPROPERTY()
    int MaxCurrentBulletNum;

    UPROPERTY()
    int TotalBulletNum;

    //============================================================================

    UFUNCTION(BlueprintOverride)
    void InitWeaponNum()
    {
        CurrentBulletNum = WeaponChildStruct.BulletNum;
        MaxCurrentBulletNum = CurrentBulletNum;
        TotalBulletNum = CurrentBulletNum * 2;
        
    }

    UFUNCTION()
    void Fire(AMainCharacter InCharacter)
    {
        // if(MainCharacter==nullptr)
        // {
        //     MainCharacter = InCharacter;
        // }

        RecoilCameraShake();
        RecoilHalfway();
        MaxRecoilY = 0;
        MaxRecoilX = 0;
        DropAvoidOffsetY = 0;
        DropAvoidOffsetX = 0;
        SpawnBullet();
        ShootHandle=System::SetTimer(this,n"SpawnBullet",WeaponChildStruct.FireFrequency,true);

        
    }

    UFUNCTION()
    void StopFire()
    {

        System::ClearAndInvalidateTimerHandle(ShootHandle);
        RecoilDown();
        CurrentShootTimes = -1;
        UpOneTime = 0;
    }

    UFUNCTION()
    void SpawnBullet()
    {
        if(MainCharacter.CurrentState != ECharacterState::STATE_SPRINT && MainCharacter.CurrentState != ECharacterState::STATE_RELORD)
        {
            if(CurrentBulletNum>0)
            {
                FVector SLoc=SkeletalMesh.GetSocketLocation(n"FireLoc");
                FRotator RLoc=SkeletalMesh.GetSocketRotation(n"FireLoc");
                FHitResult FireTraceOutHit;

                TArray<AActor> IgnoreActors;
                IgnoreActors.Add(Cast<AActor>(MainCharacter)); 	
                TArray<EObjectTypeQuery> ObjectTypes;
                ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
                ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
                ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
                ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);

                
                
                FVector StartPoint = MainCharacter.Camera.GetWorldLocation();
                FVector EndPoint = StartPoint + MainCharacter.Camera.GetForwardVector()*1000.f;
                //bool bIsHit = System::LineTraceSingle(SLoc,EndPoint,ETraceTypeQuery::TraceTypeQuery3,false,IgnoreActors,EDrawDebugTrace::ForDuration,FireTraceOutHit,true);
                bool bIsHit = System::LineTraceSingleForObjects(SLoc,EndPoint,ObjectTypes,false,IgnoreActors,EDrawDebugTrace::None,FireTraceOutHit,true);
                if(bIsHit)
                {   
                    //System::PrintString(FireTraceOutHit.GetActor().GetName().ToString());
                    DrawFireResult(FireTraceOutHit);
                }
                CurrentBulletNum--;
                AddRecoil();
            }
            else 
            {
                // //RecoilDown();
                // StopUp();
                // StopFire();
                // if(TotalBulletNum!=0)
                // {
                //     CallReloadMontage();
                // }
                SkeletalMesh.PlayAnimation(WeaponEmptyFire,false);
                AddEmptyRecoil();
            }
        }
        else 
        {
            StopFire();
        }
    }
    UFUNCTION(BlueprintEvent)
    void DrawFireResult(FHitResult TraceHit){}
    UFUNCTION(BlueprintEvent)
    void AddEmptyRecoil(){}

    UFUNCTION()
    void Reload()
    {
        if(CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum+CurrentBulletNum>=MaxCurrentBulletNum && TotalBulletNum>0)
        {
            TotalBulletNum -= MaxCurrentBulletNum-CurrentBulletNum;
            CurrentBulletNum = MaxCurrentBulletNum;
        }
        else if(CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum+CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum>0)
        {
            CurrentBulletNum +=TotalBulletNum;
            TotalBulletNum = 0;
        }

    }
    UFUNCTION(BlueprintEvent)
    void CallUIReloadUpdate(){}
    UFUNCTION(BlueprintEvent)
    void CallReloadMontage(){}

}