class FusedBounds
{
    FusedBounds()
    {}

    FusedBounds(Atmos::Spatial::Point3D position, array<Arca::RelicID> ids)
    {
        this.position = position;
        this.ids = ids;
    }
    
    void MoveTo(Atmos::Spatial::Point3D position)
    {
        this.position = position;
        MoveAllBounds();
    }
    
    Atmos::Spatial::Point3D Position() const
    {
        return position;
    }
    
    private Atmos::Spatial::Point3D position;
    private array<Arca::RelicID> ids;
    
    private void MoveAllBounds()
    {
        for(uint i = 0; i < this.ids.length(); ++i)
        {
            const auto id = ids[i];
            Arca::Reliquary::Do(Atmos::Spatial::MoveBoundsTo(id, position));
        }
    }
}