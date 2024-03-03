namespace Audio
{
    class Music
    {
        Music(Atmos::Asset::Audio asset, float volume)
        {
            const auto sound = Arca::Reliquary::Do(Arca::Create<Atmos::Audio::UniversalSound>(asset, volume));
            this.soundID = sound.ID();
            this.loopSound = LoopSound(sound.ID());
        }
        
        void Pause()
        {
            Arca::Reliquary::Do(Atmos::Audio::PauseSound(soundID));
        }
        
        void Resume()
        {
            Arca::Reliquary::Do(Atmos::Audio::ResumeSound(soundID));
        }

        private Arca::RelicID soundID;
        private LoopSound loopSound;
    }
}