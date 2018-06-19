using System;
using System.IO;
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

                Console.WriteLine();
                Console.WriteLine("Testing File Path Support:");
                Console.WriteLine("==========================");

                var fileHandler_Path = fileEngine.CreateFileHandler(filePath);

                var lateLabel_Path = new LateValue<ContentLabel>();
                fileHandler_Path.GetLabelAsync(lateLabel_Path);
                ContentLabel contentLabel_Path = lateLabel_Path.AwaitValue();

                Console.WriteLine();
                Console.WriteLine("File: " + filePath + " has content label: " + contentLabel_Path?.Label?.Name);


                Console.WriteLine();
                Console.WriteLine("Testing Stream Support:");
                Console.WriteLine("=======================");

                using (Stream stream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                {
                    var fileHandler_Stream = fileEngine.CreateFileHandler(stream, filePath);

                    var lateLabel_Stream = new LateValue<ContentLabel>();
                    fileHandler_Stream.GetLabelAsync(lateLabel_Stream);
                    ContentLabel contentLabel_Stream = lateLabel_Stream.AwaitValue();

                    Console.WriteLine();
                    Console.WriteLine("File: " + filePath + " has content label: " + contentLabel_Stream?.Label?.Name);
                }


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
