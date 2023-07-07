class AWeaponBase:AActor
{
    
    UPROPERTY(DefaultComponent)
    USkeletalMeshComponent SkeletalMesh;
    
    UPROPERTY()
    UClass Bullet;

    FTimerHandle ShootHandle;

    UPROPERTY()
    AMainCharacter MainCharacter;

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
        
        
        //System::LineTraceMulti(StartPoint,EndPoint,ETraceTypeQuery::TraceTypeQuery1,false,nullptr,EDrawDebugTrace::ForDuration,FireTraceOutHit);
       //FRotator FinalRotator = AFPS_FuncLib::FindLookAtRotator(SLoc,MainCharacter.TargetPoint.GetWorldLocation());
        //AActor SpawnBullet=SpawnActor(Bullet,SLoc,FinalRotator);
        //SpawnBullet.ActorScale3D=FVector(0.5,0.5,0.5);
    }

}