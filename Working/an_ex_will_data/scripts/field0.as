void main()
{
    Entity::Avatar avatar(
        Arca::Reliquary::Do(Atmos::Entity::FindByName("avatar")).ID(),
        Arca::Reliquary::Do(Arca::Create<Atmos::Render::DynamicImage>(
            Assets::Image::character(),
            0,
            Assets::ImageMaterial::basic(),
            Atmos::Render::Color(255, 255, 255, 255),
            Atmos::Spatial::Point3D(48, 48, 32),
            Atmos::Spatial::Scalers2D(1, 1),
            0)).ID(),
        Entity::CharacterAnimation(
            Atmos::IntRange(16, 23),
            Modulation::Linear),
        Entity::CharacterAnimation(
            Atmos::IntRange(8, 15),
            Modulation::Linear),
        Entity::CharacterAnimation(
            Atmos::IntRange(24, 31),
            Modulation::Linear),
        Entity::CharacterAnimation(
            Atmos::IntRange(0, 7),
            Modulation::Linear),
        Atmos::Time::ToNanoseconds(Atmos::Time::Milliseconds(125)));
    
    Camera managedCamera;
    managedCamera.Follow(avatar.ImageID());
     
    const auto music = Audio::Music(Assets::Audio::sevenBillionPeople(), 1.0);

    while(true)
    {
        avatar.Execute();
        
        Arca::Reliquary::Do(Atmos::Scripting::Suspend(Atmos::CurrentScript()));
    }
}