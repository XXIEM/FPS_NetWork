class AMainCharacter:AFPS_NetworkCharacter
{
    UPROPERTY(DefaultComponent,Attach=CharacterMesh0,AttachSocket=head)
    UCameraComponent Camera;
    default Camera.bUsePawnControlRotation = true;





    UPROPERTY()
    UClass Weapon_AR4;

    //绘制后的枪
    UPROPERTY()
    AActor SpawnGun;

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

}