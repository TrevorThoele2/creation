class ActionStabilizer
{
    ActionStabilizer(Atmos::Asset::Action checkAsset)
    {
        this.checkAsset = checkAsset;
        
        Arca::Reliquary::On(Atmos::Input::OnActionPressed(this.HandlePressed));
        Arca::Reliquary::On(Atmos::Input::OnActionDepressed(this.HandleDepressed));
    }
    
    bool IsActive() const
    {
        return isActive;
    }
    
    private Atmos::Asset::Action checkAsset;
    private bool isActive = false;
    
    private void HandlePressed(Atmos::Input::ActionPressed signal)
    {
        if(signal.action == checkAsset)
            isActive = true;
    }
    
    private void HandleDepressed(Atmos::Input::ActionDepressed signal)
    {
        if(signal.action == checkAsset)
            isActive = false;
    }
}