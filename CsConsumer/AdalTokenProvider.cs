using System;
using System.Threading.Tasks;
using Microsoft.IdentityModel.Clients.ActiveDirectory;

namespace CsConsumer
{
    /// <summary>
    /// 
    /// </summary>
    /// <seealso cref="https://docs.microsoft.com/en-us/azure/active-directory/develop/active-directory-v2-libraries"/>
    public class AdalTokenProvider : ITokenProvider
    {
        private string clientId;

        /// <summary>
        /// Create a new instance of the <see cref="AdalTokenProvider"/> class.
        /// </summary>
        /// <param name="clientId">
        /// ADAL client id for MIP Universal Sample App.
        /// To create your own client id, follow instructions here: https://docs.microsoft.com/en-us/azure/active-directory/develop/active-directory-devquickstarts-dotnet
        /// </param>
        public AdalTokenProvider(string clientId)
        {
            this.clientId = clientId;
        }

        public string AcquireToken(string userId, string authority, string resource)
        {
            AuthenticationContext context = new AuthenticationContext(authority);
            //context.TokenCache.Clear();

            string token = null;
            try
            {
                //Task<AuthenticationResult> acquireTask = context.AcquireTokenAsync(resource, clientId, new Uri("com.microsoft.rms-sharing-for-win://authorize"), new PlatformParameters(PromptBehavior.Auto, true));
                Task<AuthenticationResult> acquireTask = context.AcquireTokenAsync(resource, this.clientId, new Uri("com.microsoft.rms-sharing-for-win://authorize"), new PlatformParameters(PromptBehavior.Auto));
                acquireTask.Wait();
                token = acquireTask.Result.AccessToken;
            }
            catch (AdalException ex)
            {
            }

            return token;
        }


    }
}
