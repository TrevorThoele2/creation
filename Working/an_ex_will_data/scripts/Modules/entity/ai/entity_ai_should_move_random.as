namespace Entity
{
    namespace AI
    {
        class ShouldMoveRandom
        {
            ShouldMoveRandom(double chancePerSecond)
            {
                if (chancePerSecond > 1)
                    this.chancePerSecond = 1;
                else if (chancePerSecond < 0)
                    this.chancePerSecond = 0;
                else
                    this.chancePerSecond = chancePerSecond;
            }
            
            bool Execute(Character@)
            {
                if (timer.Elapsed().Count() >= this.second.Count())
                {
                    timer.Restart();
                    const auto random = Arca::Reliquary::Do(Atmos::Random::GenerateDouble(Atmos::DoubleRange(0, 1)));
                    return random <= this.chancePerSecond;
                }
                else
                    return false;
            }
            
            private double chancePerSecond;
            private Atmos::Time::Nanoseconds second = Atmos::Time::ToNanoseconds(Atmos::Time::Seconds(1));
            private Atmos::Time::Stopwatch timer = Atmos::Time::CreateFrameStopwatch();
        }
    }
}