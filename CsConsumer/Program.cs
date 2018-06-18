using System;
using CLI;

namespace CsConsumer
{
    class Program
    {
        static void Main(string[] args)
        {
            string clientId = System.Configuration.ConfigurationManager.AppSettings["clientId"];
            string oAuth2Authority = System.Configuration.ConfigurationManager.AppSettings["oAuth2Authority"];
            string oAuth2Resource = System.Configuration.ConfigurationManager.AppSettings["oAuth2Resource"];
            string applicationId = System.Configuration.ConfigurationManager.AppSettings["applicationId"];
            string applicationName = System.Configuration.ConfigurationManager.AppSettings["applicationName"];

            var identity = new Identity(@"");

            var challenge = new AuthDelegate.OAuth2Challenge(
                    oAuth2Authority,
                    oAuth2Resource);

            var token = new AuthDelegate.OAuth2Token();

            AuthDelegate authDelegate = new AuthDelegateImpl(new AdalTokenProvider(clientId));
            var result = authDelegate.AcquireOAuth2Token(
                identity,
                challenge,
                token);

            Console.WriteLine(token.AccessToken);


            var applicationInfo = new ApplicationInfo(
                applicationId,
                applicationName);

            string storagePath = System.IO.Path.GetTempPath() + @"\sample_app_data";


            var settings = new FileProfile.Settings(storagePath, false, authDelegate, applicationInfo);

            var lateFileProfile = new LateValue<FileProfile>();

            FileProfile.LoadAsync(settings, lateFileProfile);
            FileProfile profile = lateFileProfile.AwaitValue();


            FileEngine.Settings engineSettings = new FileEngine.Settings("1234", "");

            var lateFileEngine = new LateValue<FileEngine>();

            profile.AddEngineAsync(engineSettings, lateFileEngine);

            try
            {
                FileEngine fileEngine = lateFileEngine.AwaitValue();
            }
            catch (Exception ex)
            {
                Console.WriteLine("====================");
                Console.WriteLine(ex.Message);
                Console.WriteLine("====================");
            }


            Console.WriteLine();
            Console.WriteLine("Press any key ...");
            Console.ReadKey();
        }
    }
}
