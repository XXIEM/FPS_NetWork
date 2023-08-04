class AWeaponBase:AFPS_WeaponBase
{
    UPROPERTY(DefaultComponent)
    USceneComponent Scene;

    UPROPERTY(DefaultComponent,Attach = Scene)
    USkeletalMeshComponent SkeletalMesh;

    UPROPERTY(DefaultComponent,Attach = SkeletalMesh)
    USceneComponent AimPointTest;

    UPROPERTY(DefaultComponent,Attach = SkeletalMesh)
    USphereComponent Sphere;
    
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


    UFUNCTION(BlueprintEvent)
    void AddRecoil(){}

    UFUNCTION(BlueprintEvent)
    void RecoilDown(){}

    UFUNCTION(BlueprintEvent)
    void RecoilCameraShake(){}

    UFUNCTION(BlueprintEvent)
    void RecoilHalfway(){}
    //------------------------------------

    //--------------换弹部分--------------
    UPROPERTY()
    int CurrentBulletNum = 30;

    UPROPERTY()
    int MaxCurrentBulletNum;

    UPROPERTY()
    int TotalBulletNum;

    //============================================================================


    UFUNCTION()
    void Fire(AMainCharacter InCharacter)
    {
        if(MainCharacter==nullptr)
        {
            MainCharacter = InCharacter;
        }

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
            FVector SLoc=SkeletalMesh.GetSocketLocation(n"FireLoc");
            FRotator RLoc=SkeletalMesh.GetSocketRotation(n"FireLoc");
            FHitResult FireTraceOutHit;

            TArray<AActor> IgnoreActors;
            IgnoreActors.Add(Cast<AActor>(MainCharacter)); 	
            TArray<EObjectTypeQuery> ObjectTypes;
            ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
            
            
            FVector StartPoint = MainCharacter.Camera.GetWorldLocation();
            FVector EndPoint = StartPoint + MainCharacter.Camera.GetForwardVector()*3000.f;
            //bool bIsHit = System::LineTraceSingle(SLoc,EndPoint,ETraceTypeQuery::TraceTypeQuery3,false,IgnoreActors,EDrawDebugTrace::ForDuration,FireTraceOutHit,true);
            bool bIsHit = System::LineTraceSingleForObjects(SLoc,EndPoint,ObjectTypes,false,IgnoreActors,EDrawDebugTrace::ForDuration,FireTraceOutHit,true);
            if(bIsHit)
            {
                System::PrintString(FireTraceOutHit.GetActor().GetName().ToString());
            }
            AddRecoil();
    }

    UFUNCTION()
    void Reload()
    {
        if(CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum+CurrentBulletNum>MaxCurrentBulletNum && TotalBulletNum>0)
        {
            TotalBulletNum -= CurrentBulletNum;
            CurrentBulletNum = MaxCurrentBulletNum;
        }
        else if(CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum+CurrentBulletNum<MaxCurrentBulletNum && TotalBulletNum>0)
        {
            CurrentBulletNum +=TotalBulletNum;
            TotalBulletNum = 0;
        }

    }


}