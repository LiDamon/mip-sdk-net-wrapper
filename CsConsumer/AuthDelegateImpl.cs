using NetMip;

namespace CsConsumer
{
    internal class AuthDelegateImpl : AuthDelegate
    {
        private readonly ITokenProvider tokenProvider;

        public AuthDelegateImpl(ITokenProvider tokenProvider)
        {
            this.tokenProvider = tokenProvider;
        }

        public override bool AcquireOAuth2Token(Identity identity, OAuth2Challenge challenge, OAuth2Token token)
        {
            string accessToken = tokenProvider.AcquireToken(identity.Email, challenge.Authority, challenge.Resource);
            token.AccessToken = accessToken;
            return true;
        }
    }
}
