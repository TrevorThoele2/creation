namespace Modulation
{  
    funcdef void On(double);
    funcdef double Interpolation(double);
    
    class Node
    {
        On@ on;
        Interpolation@ interpolation;
        Atmos::Time::Nanoseconds startAt;
        Atmos::Time::Nanoseconds duration;
        
        double startValue;
        double endValue;
        
        Node()
        {}
        
        Node(
            double startValue,
            double endValue,
            Atmos::Time::Nanoseconds startAt,
            Atmos::Time::Nanoseconds duration,
            Interpolation@ interpolation,
            On@ on)
        {
            this.startValue = startValue;
            this.endValue = endValue;
            this.startAt = startAt;
            this.duration = duration;
            @this.interpolation = @interpolation;
            @this.on = @on;
        }
    }
}