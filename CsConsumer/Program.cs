using CLI;
using System;

namespace CsConsumer
{
    class Program
    {
        static void Main(string[] args)
        {
            FileEngine.Settings e = new FileEngine.Settings("id", "clientData", "locale");

            Console.WriteLine();
            Console.WriteLine("Initialised...");
            WriteSettings("\t", e);

            e.SessionId = "sessionId";
            e.CustomSettings = new Pair<string, string>[]
            {
                new Pair<string, string>("key1", "value1"),
                new Pair<string, string>("key2", "value2"),
            };

            Console.WriteLine();
            Console.WriteLine("Changes made...");
            WriteSettings("\t", e);

            Console.WriteLine();
            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey(true);
        }

        static void WriteSettings(string prefix, FileEngine.Settings e)
        {
            Console.Write(prefix);
            Console.WriteLine("Id= " + e.Id);
            Console.Write(prefix);
            Console.WriteLine("ClientData= " + e.ClientData);
            Console.Write(prefix);
            Console.WriteLine("Locale= " + e.Locale);
            Console.Write(prefix);
            Console.WriteLine("SessionId= " + e.SessionId);
            Console.Write(prefix);
            Console.WriteLine("CustomSettings= ");
            foreach (var pair in e.CustomSettings)
            {
                Console.WriteLine("\t" + pair.First + "= " + pair.Second);
            }
        }
    }
}
