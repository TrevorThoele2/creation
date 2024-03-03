namespace Modulation
{
    double Linear(double delta)
    {
        return delta;
    }
    
    double Smoothstep(double delta)
    {
        return delta * delta * (3 - 2 * delta);
    }
}