class AWeaponBase:AFPS_WeaponBase
{
    UPROPERTY(DefaultComponent)
    USceneComponent Scene;

    UPROPERTY(DefaultComponent,Attach = Scene)
    USkeletalMeshComponent SkeletalMesh;

    UPROPERTY(DefaultComponent,Attach = SkeletalMesh)
    USceneComponent AimPointTest;
    
    UPROPERTY()
    UClass Bullet;

    FTimerHandle ShootHandle;

    UPROPERTY()
    AMainCharacter MainCharacter;



    UFUNCTION(BlueprintEvent)
    void AddRecoil(){}

    //============================================================================
    UFUNCTION()
    void Fire(AMainCharacter InCharacter)
    {
        MainCharacter = InCharacter;
        SpawnBullet();
        ShootHandle=System::SetTimer(this,n"SpawnBullet",0.15,true);
        
    }

    UFUNCTION()
    void StopFire()
    {

        System::ClearAndInvalidateTimerHandle(ShootHandle);
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


}