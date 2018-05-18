namespace Modulation
{  
    class Modulator
    {
        Modulator(array<Modulation::Node> allNodes)
        {
            this.allNodes = allNodes;
            ResetNodesLeft();
        }
        
        void Pause()
        {
            isPaused = true;
            timer.Pause();
        }
        
        void Resume()
        {
            isPaused = false;
            timer.Resume();
        }
        
        void Restart()
        {
            isPaused = false;
            ResetNodesLeft();
            timer.Restart();
        }
        
        bool Execute()
        {
            if (isPaused)
                return IsDone();
        
            const auto elapsed = ToWorkableTime(timer.Elapsed());
        
            for(int i = nodesLeft.length() - 1; i >= 0; --i)
            {
                const auto node = nodesLeft[i];
                if (!IsNodeDone(node, elapsed))
                    ExecuteNode(node, elapsed);
                else
                    nodesLeft.removeAt(i);
            }
            
            return IsDone();
        }
        
        private array<Modulation::Node> allNodes;
        private array<Modulation::Node@> nodesLeft;
        private Atmos::Time::Stopwatch timer = Atmos::Time::CreateFrameStopwatch();
        private bool isPaused = false;
        
        private bool IsDone() const
        {
            return nodesLeft.length() == 0;
        }
        
        private void ResetNodesLeft()
        {
            this.nodesLeft.resize(this.allNodes.length());
            for(uint i = 0; i < this.allNodes.length(); ++i)
                @this.nodesLeft[i] = @this.allNodes[i];
        }
        
        private bool IsNodeDone(Modulation::Node node, double elapsed) const
        {
            return elapsed >= ToWorkableTime(node.startAt) + ToWorkableTime(node.duration);
        }
        
        private void ExecuteNode(Modulation::Node node, double elapsed) const
        {
            if (elapsed < ToWorkableTime(node.startAt))
                return;
        
            const auto nodeElapsed = elapsed - ToWorkableTime(node.startAt);
            const auto durationDelta = nodeElapsed / ToWorkableTime(node.duration);
            if (durationDelta > 1.0)
            {
                node.on(node.endValue);
                return;
            }
            
            const auto distance = node.endValue - node.startValue;
            const auto interpolated = node.startValue + distance * node.interpolation(durationDelta);
            node.on(interpolated);
        }
        
        private double ToWorkableTime(Atmos::Time::Point<Atmos::Time::Nanoseconds> timePoint) const
        {
            return double(timePoint.TimeSinceEpoch().Count());
        }
    }
}