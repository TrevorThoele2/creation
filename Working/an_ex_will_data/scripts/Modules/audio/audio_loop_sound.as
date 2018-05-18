namespace Audio
{
    class LoopSound
    {
        LoopSound()
        {}

        LoopSound(Arca::RelicID id)
        {
            this.id = id;
            this.endless = true;
        }
        
        LoopSound(Arca::RelicID id, int times)
        {
            this.id = id;
            this.times = times;
            this.endless = false;
        }
        
        private Arca::RelicID id = 0;
        private bool endless = false;
        private int times = 0;
        
        private void HandleSoundFinished(Atmos::Audio::SoundFinished signal)
        {
            if (signal.id == id)
                Arca::Reliquary::Do(Atmos::Audio::RestartSound(id));
        }
    }
}