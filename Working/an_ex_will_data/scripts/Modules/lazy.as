mixin class Lazy
{
    protected void AttemptRetrieve()
    {
        if (!hasRetrieved)
        {
            value = Retrieve();
            hasRetrieved = true;
        }
    }
    
    private bool hasRetrieved = false;
}