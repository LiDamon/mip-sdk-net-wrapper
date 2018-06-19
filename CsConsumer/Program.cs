using System;
using CLI;

namespace CsConsumer
{
    class Program
    {
        static void Main(string[] args)
        {
            string clientId = System.Configuration.ConfigurationManager.AppSettings["clientId"];
            string applicationId = System.Configuration.ConfigurationManager.AppSettings["applicationId"];
            string applicationName = System.Configuration.ConfigurationManager.AppSettings["applicationName"];

            try
            {
                AuthDelegate authDelegate = new AuthDelegateImpl(new AdalTokenProvider(clientId));

                var applicationInfo = new ApplicationInfo(
                    applicationId,
                    applicationName);

                string storagePath = System.IO.Path.GetTempPath() + @"\sample_app_data";


                var settings = new FileProfile.Settings(storagePath, false, authDelegate, applicationInfo);

                var lateFileProfile = new LateValue<FileProfile>();

                Console.WriteLine();
                Console.WriteLine("Async load file profile...");

                FileProfile.LoadAsync(settings, lateFileProfile);
                FileProfile profile = lateFileProfile.AwaitValue();


                FileEngine.Settings engineSettings = new FileEngine.Settings("1234", "");

                var lateFileEngine = new LateValue<FileEngine>();

                Console.WriteLine();
                Console.WriteLine("Async add engine...");

                profile.AddEngineAsync(engineSettings, lateFileEngine);
                FileEngine fileEngine = lateFileEngine.AwaitValue();


                Console.WriteLine();
                Console.WriteLine("Getting labels...");

                Label[] labels = fileEngine.ListSensitivityLabels();

                Console.WriteLine();
                Console.WriteLine("Available labels:");
                foreach (var label in labels)
                {
                    DisplayLabel("", label);
                }

                const string filePath = @"Unlabelled.docx";

                var fileHandler = fileEngine.CreateFileHandler(filePath);
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine("====================");
                Console.WriteLine(ex.Message);
                Console.WriteLine("====================");
            }

            Console.WriteLine();
            Console.WriteLine("Press any key ...");
            Console.ReadKey();
        }

        private static void DisplayLabel(string prefix, Label label)
        {
            Console.Write(prefix);
            Console.WriteLine("Name=", label.Name);
            foreach (var child in label.Children)
            {
                DisplayLabel(prefix + "\t", child);
            }
        }
    }
}
