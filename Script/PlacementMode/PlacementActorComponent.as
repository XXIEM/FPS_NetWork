
enum EPlacementActorStateType 
{
    Place,
    UnPlace,
    President,//放置回合结束后切换为这个状态
}

delegate void FOnPlacementStateChange(EPlacementActorStateType State,AActor InSpawner);
UCLASS()
class UPlacementActorComponent : UActorComponent
{

    UPROPERTY(NotVisible)
    private EPlacementActorStateType State = EPlacementActorStateType::UnPlace;

    UPROPERTY()
    FName PlacementActorName = NAME_None;

    /**
    *ExecuteWhenStateChange
    *Need To Bind In Owner
    */
    UPROPERTY()
    FOnPlacementStateChange OnPlacementStateChange;
    
    UPROPERTY()
    UTexture2D UITexture;
    
    /**
     * @description: 改变Actor的状态
     * @param StateToChange想要改变的状态
     * @return 是否改变成功 
     */    
    UFUNCTION(Server)
    void ChangeState_Server(EPlacementActorStateType StateToChange,AActor InSpawner)
    {
        ChangeState_Multicast(StateToChange,InSpawner);
    }
    UFUNCTION(NetMulticast)
    void ChangeState_Multicast(EPlacementActorStateType StateToChange,AActor InSpawner)
    {
        State = StateToChange;
        switch(StateToChange)
        {
            
            case EPlacementActorStateType::Place:
            {
                //TODO:    
                                   
                GetOwner().SetActorEnableCollision(true);
                break;
            }
            case EPlacementActorStateType::UnPlace:
            {
                //TODO:
                
                GetOwner().SetActorEnableCollision(false); 
                break;
            }
            case EPlacementActorStateType::President:
            {
                //TODO:
                GetOwner().SetActorEnableCollision(true);
                break;
            }
            default:
            {
                break;
            }
        }
        OnPlacementStateChange.ExecuteIfBound(State,InSpawner);
    }
}