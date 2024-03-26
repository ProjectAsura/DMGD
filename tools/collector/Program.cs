using System;
using System.IO;
using System.Text;

namespace collector
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("collector.exe {rootPath} {exeName} {header}");
                Console.WriteLine("[rootPath] : ソースコードのルートディレクトリを指定します. (ex) C:\\root\\test");
                Console.WriteLine("[exeName]  : 出力するバイナリ名を指定します. (ex) C:\\root\\test\\bin\\game.gb");
                Console.WriteLine("[header]   : ファイル先頭に付加する文字列を指定します.");
                return;
            }

            var rootPath = args[0];
            var output   = args[1];
            var header   = (args.Length >= 3) ? args[2] : null;

            if (!Directory.Exists(rootPath))
            {
                Console.Error.WriteLine($"Root Path Not Found. Path={rootPath}");
                return;
            }

            var files = Directory.GetFiles(rootPath, "*.c", SearchOption.AllDirectories);

            var sources = new StringBuilder();
            var builder = new StringBuilder();

            if (header != null)
            {
                builder.Append(header);
                builder.Append("\n");
            }

            builder.Append($"# Compile {files.Length} Files.\n");
            foreach (var sourceName in files)
            {
                var srcName = sourceName.ToLower();
                srcName = srcName.Replace("c:\\", "c$:\\");
                var objName = Path.ChangeExtension(srcName, ".o");
                sources.Append(objName + " ");
                builder.Append($"build {objName}: compile {srcName}\n");
            }
            builder.Append("# Link\n");
            builder.Append($"build {output}: link {sources}\n");

            var listName = Path.Combine(rootPath, "collected.ninja");
            using (var stream = File.Create(listName))
            using (var writer = new StreamWriter(stream, Encoding.UTF8))
            {
                writer.Write(builder.ToString());
            }

            Console.WriteLine($"File List Output! Path ={listName}");
        }
    }
}
