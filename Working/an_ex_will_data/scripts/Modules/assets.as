namespace Assets
{
    namespace Action
    {
        CachedAsset moveLeft("MoveLeft");
        CachedAsset moveUp("MoveUp");
        CachedAsset moveRight("MoveRight");
        CachedAsset moveDown("MoveDown");
        
        class CachedAsset : Lazy
        {
            CachedAsset(string name)
            {
                this.name = name;
            }
        
            Atmos::Asset::Action opCall()
            {
                AttemptRetrieve();
                return value;
            }
            
            private Atmos::Asset::Action Retrieve()
            {
                return Arca::Reliquary::Do(Atmos::Asset::FindByName<Atmos::Asset::Action>(name));
            }
            
            private string name;
            private Atmos::Asset::Action value;
        }
    }

    namespace Audio
    {
        CachedAsset sevenBillionPeople("7 Billion People");
        
        class CachedAsset : Lazy
        {
            CachedAsset(string name)
            {
                this.name = name;
            }
        
            Atmos::Asset::Audio opCall()
            {
                AttemptRetrieve();
                return value;
            }
            
            private Atmos::Asset::Audio Retrieve()
            {
                return Arca::Reliquary::Do(Atmos::Asset::FindByName<Atmos::Asset::Audio>(name));
            }
            
            private string name;
            private Atmos::Asset::Audio value;
        }
    }
    
    namespace Image
    {
        CachedAsset character("character");
        
        class CachedAsset : Lazy
        {
            CachedAsset(string name)
            {
                this.name = name;
            }
        
            Atmos::Asset::Image opCall()
            {
                AttemptRetrieve();
                return value;
            }
            
            private Atmos::Asset::Image Retrieve()
            {
                return Arca::Reliquary::Do(Atmos::Asset::FindByName<Atmos::Asset::Image>(name));
            }
            
            private string name;
            private Atmos::Asset::Image value;
        }
    }
    
    namespace ImageMaterial
    {
        CachedAsset basic("default_image");
        
        class CachedAsset : Lazy
        {
            CachedAsset(string name)
            {
                this.name = name;
            }
        
            Atmos::Asset::ImageMaterial opCall()
            {
                AttemptRetrieve();
                return value;
            }
            
            private Atmos::Asset::ImageMaterial Retrieve()
            {
                return Arca::Reliquary::Do(Atmos::Asset::FindByName<Atmos::Asset::ImageMaterial>(name));
            }
            
            private string name;
            private Atmos::Asset::ImageMaterial value;
        }
    }
}