namespace CsConsumer
{
    public interface ITokenProvider
    {
        string AcquireToken(string identity, string challenge, string resource);
    }
}
