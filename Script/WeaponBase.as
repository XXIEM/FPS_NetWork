class AWeaponBase:AActor
{
    
    UPROPERTY(DefaultComponent)
    USkeletalMeshComponent SkeletalMesh;
    
    UPROPERTY()
    UClass Bullet;

    FTimerHandle ShootHandle;

    FVector ScreenCenter;

    UPROPERTY()
    AMainCharacter MainCharacter;

    UFUNCTION()
    void Fire()
    {

        
        
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

        //FRotator FinalRotator = AFuncLibForAS::FindLookAtRotator(SLoc,ScreenCenter);
        //AActor SpawnBullet=SpawnActor(Bullet,SLoc,FinalRotator);
        
        //SpawnBullet.ActorScale3D=FVector(0.5,0.5,0.5);
    }

}