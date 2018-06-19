using System;
using System.Collections.Generic;
using System.IO;
using NetMip;

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
                string storagePath = System.IO.Path.GetTempPath() + @"\sample_app_data";

                Console.WriteLine();
                Console.WriteLine("Create the FileApi:");
                Console.WriteLine("-------------------");

                FileApi fileApi = new FileApi(
                    new AdalTokenProvider(clientId),
                    applicationId,
                    applicationName,
                    storagePath);


                Console.WriteLine();
                Console.WriteLine("List Available Labels:");
                Console.WriteLine("----------------------");

                IEnumerable<Label> labels = fileApi.ListLabels();

                Console.WriteLine();
                Console.WriteLine("Available labels:");
                foreach (var label in labels)
                {
                    DisplayLabel("", label);
                }


                const string filePath = @"Unlabelled.docx";

                Console.WriteLine();
                Console.WriteLine("Testing File Path Support:");
                Console.WriteLine("--------------------------");

                string fileLabelName = fileApi.GetFileLabel(filePath);

                Console.WriteLine();
                Console.WriteLine("File: " + filePath + " has content label: " + fileLabelName);


                Console.WriteLine();
                Console.WriteLine("Testing Stream Support:");
                Console.WriteLine("-----------------------");

                using (Stream stream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                {
                    string fileLabelName_Stream = fileApi.GetFileLabel(stream, filePath);

                    Console.WriteLine();
                    Console.WriteLine("File: " + filePath + " has content label: " + fileLabelName_Stream);
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
