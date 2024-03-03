namespace Entity
{
    namespace AI
    {
        class ShouldMoveInterval
        {
            ShouldMoveInterval(Atmos::Time::Nanoseconds nanoseconds)
            {
                this.nanoseconds = nanoseconds;
            }
            
            bool Execute(Character@)
            {
                if (timer.Elapsed().Count() >= this.nanoseconds.Count())
                {
                    timer.Restart();
                    return true;
                }
                else
                    return false;
            }
            
            private Atmos::Time::Nanoseconds nanoseconds;
            private Atmos::Time::Stopwatch timer = Atmos::Time::CreateFrameStopwatch();
        }
    }
}