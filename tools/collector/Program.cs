using System;
using System.IO;
using System.Text;

namespace collector
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("collector.exe inputDir outDir binName (ruleNinja)");
                Console.WriteLine("[inputPath] : ソースコードのルートディレクトリを指定します. (ex) C:\\root\\test");
                Console.WriteLine("[outputDir] : 出力ディレクトリです.");
                Console.WriteLine("[binName]   : 出力するバイナリ名を指定します.フォルダパスは含めないで下さい. (ex) game.gb");
                Console.WriteLine("[ruleNinja] : (オプション) ファイル先頭に付加する文字列を指定します.");
                return;
            }

            var rootPath = Path.GetFullPath(args[0]);
            var outPath  = Path.GetFullPath(args[1]);
            var binName  = CorrectPath(Path.Combine(outPath, args[2]));
            var rulePath = (args.Length >= 4) ? args[3] : null;

            if (!Directory.Exists(rootPath))
            {
                Console.Error.WriteLine($"Root Path Not Found. Path=\"{rootPath}\".");
                return;
            }

            if (!Directory.Exists(outPath))
            {
                Directory.CreateDirectory(outPath);
            }

            var files = Directory.GetFiles(rootPath, "*.c", SearchOption.AllDirectories);

            if (files.Length == 0)
            {
                Console.Error.WriteLine("C File Not Found.");
                return;
            }

            var sources = new StringBuilder();
            var builder = new StringBuilder();

            if (!string.IsNullOrEmpty(rulePath) && File.Exists(rulePath))
            {
                using (var reader = new StreamReader(rulePath))
                {
                    string line;
                    while((line = reader.ReadLine() ) != null)
                    {
                        builder.Append(line);
                        builder.Append("\n");
                    }
                }
            }

            builder.Append($"# Compile {files.Length} Files.\n");
            foreach (var sourceName in files)
            {
                var srcName = CorrectPath(sourceName);
                var objName = Path.GetFullPath(sourceName);
                objName = objName.Replace(rootPath + "\\", outPath + "\\");
                objName = Path.ChangeExtension(objName, ".o");
                objName = CorrectPath(objName);
                sources.Append(objName + " ");
                builder.Append($"build {objName}: compile {srcName}\n");
            }
            builder.Append("# Link\n");
            builder.Append($"build {binName}: link {sources}\n");

            var listName = Path.Combine(outPath, "build.ninja");
            using (var stream = File.Create(listName))
            using (var writer = new StreamWriter(stream, Encoding.ASCII))
            {
                writer.Write(builder.ToString());
            }

            Console.WriteLine($"Generate File List. Path =\"{listName}\".");
        }

        static string CorrectPath(string path)
        {
            var p = Path.GetFullPath(path);
            p = p.ToLower();
            p = p.Replace(":\\", "$:\\");
            return p;
        }
    }
}
