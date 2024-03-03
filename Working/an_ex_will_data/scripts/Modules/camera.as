class Camera
{
    Camera()
    {
        Arca::Reliquary::On(Atmos::Spatial::OnBoundsMoved(this.OnBoundsMoved));
    }

    void MoveTo(Atmos::Spatial::Point3D position)
    {
        Reset();
        
        DoMove(position);
    }
    
    void Follow(Arca::RelicID boundsID)
    {
        Reset();
        
        followingBounds = true;
        this.followingBoundsID = boundsID;
        DoMove(Atmos::Spatial::Bounds(boundsID).Position());
    }
    
    private Atmos::Render::Camera relic;
    
    private bool followingBounds = false;
    private Arca::RelicID followingBoundsID;
    
    private void Reset()
    {
        followingBounds = false;
        followingBoundsID = Arca::nullRelicID;
    }
    
    private void OnBoundsMoved(Atmos::Spatial::BoundsMoved signal)
    {
        if (!followingBounds)
            return;
        
        const auto bounds = signal.bounds;
        if (bounds.ID() != followingBoundsID)
            return;
        
        const auto position = bounds.Position();
        DoMove(position);
    }
    
    private void DoMove(Atmos::Spatial::Point3D position)
    {
        Arca::Reliquary::Do(Atmos::Spatial::MoveBoundsTo(relic.ID(), position));
    }
}