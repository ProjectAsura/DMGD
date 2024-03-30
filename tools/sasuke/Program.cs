using System;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;

namespace sasuke
{
    internal class Program
    {
        enum CommandType
        {
            Build,
            Rebuild,
            Clean,
            Run
        };

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                ShowHelp();
                return;
            }

            try
            {
                var commandType = Enum.Parse<CommandType>(args[0], true);
                var configPath  = Path.GetFullPath(args[1]);
                bool debug      = (args.Length >= 3 && args[2] == "debug");

                var config = LoadConfig(configPath);
                if (config == null)
                {
                    Console.Error.Write($"Error : Configuration File Loade Failed. path = {configPath}");
                    return;
                }

                var appendPath = debug ? "debug" : "release";
                config.Debug     = debug;
                config.OutputDir = Path.Combine(config.OutputDir, appendPath);

                switch (commandType)
                {
                    case CommandType.Build:
                        Build(config);
                        break;

                    case CommandType.Rebuild:
                        Rebuild(config);
                        break;

                    case CommandType.Clean:
                        Clean(config);
                        break;

                    case CommandType.Run:
                        Run(config);
                        break;

                    default:
                        Console.Error.WriteLine("Error : Unknown Command");
                        ShowHelp();
                        break;
                }
            }
            catch(Exception e)
            {
                Console.Error.WriteLine(e.Message);
            }
        }

        static private BuildConfig LoadConfig(string path)
        {
            if (string.IsNullOrEmpty(path) || !File.Exists(path))
            {
                return null;
            }

            try
            {
                var option = new JsonSerializerOptions
                {
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.All),
                    WriteIndented = true,
                };
                using var file   = File.OpenRead(path);
                using var stream = new StreamReader(file, Encoding.UTF8);
                var data = stream.ReadToEnd();
                return JsonSerializer.Deserialize<BuildConfig>(data, option);
            }
            catch(Exception e)
            {
                Console.Error.WriteLine(e.Message);
                return null;
            }
        }

        static private void Build(BuildConfig config)
        {
            var dir = Directory.GetCurrentDirectory();

            try
            {
                var inputDir  = Path.GetFullPath(config.InputDir);
                var outputDir = Path.GetFullPath(config.OutputDir);
                var ninjaExe  = Path.GetFullPath(config.NinjaPath);

                if (!File.Exists(ninjaExe))
                {
                    Console.Error.WriteLine($"Error : ninja.exe not found. path={ninjaExe}");
                    return;
                }

                // 入力ディレクトリの存在を確認.
                if (!Directory.Exists(inputDir))
                {
                    Console.Error.WriteLine("Error : Input Directory does not exists.");
                    return;
                }

                // 出力ディレクトリが存在しなければ作成.
                if (!Directory.Exists(outputDir))
                {
                    Directory.CreateDirectory(outputDir);
                }

                // build.ninja を生成.
                if (!CreateNinjaFile(config, CollectSources(inputDir)))
                {
                    Console.Error.WriteLine("Error : build.ninja create failed.");
                    return;
                }

                // .ninja_log を出力ディレクトリに吐き出すために出力ディレクトリをカレントにする.
                Directory.SetCurrentDirectory(outputDir);

                // Nijja ビルドを実行.
                var args = "-v -f " + Path.Combine(outputDir, "build.ninja");
                var process = Process.Start(ninjaExe, args);
                process.WaitForExit();
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e.Message);
            }
            finally
            {
                Directory.SetCurrentDirectory(dir);
            }
        }

        static private void Rebuild(BuildConfig config)
        {
            Clean(config);
            Build(config);
        }

        static private void Clean(BuildConfig config)
        {
            try
            {
                var dir = Path.GetFullPath(config.OutputDir);
                List<string> files = new List<string>();
                string[] patterns =
                {
                    "*.o",
                    "*.lst",
                    "*.map",
                    "*.gb",
                    "*~",
                    "*.rel",
                    "*.cdb",
                    "*.ihx",
                    "*.lnk",
                    "*.sym",
                    "*.asm",
                    "*.noi",
                    "*.ninja_log"
                };

                foreach (var p in patterns)
                {
                    files.AddRange(Directory.GetFiles(dir, p, SearchOption.AllDirectories));
                }
                foreach(var f in files)
                {
                    File.Delete(f);
                }
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e.Message);
            }
        }

        static private void Run(BuildConfig config)
        {
            var outputDir = Path.GetFullPath(config.OutputDir);
            var args = "-rom " + Path.Combine(outputDir, config.TargetName);
            _ = Process.Start(Path.GetFullPath(config.EmulatorPath), args);
        }

        static private void ShowHelp()
        {
            Console.WriteLine("sasuke.exe <config> <command> (debug)");
            Console.WriteLine("[command] : ビルドコマンドを指定します. 以下のコマンドが指定可能です.");
            Console.WriteLine("            - Build   ビルド処理を実行します.");
            Console.WriteLine("            - Rebuild リビルド処理を実行します.");
            Console.WriteLine("            - Clean   クリーン処理を実行します.");
            Console.WriteLine("            - Run     出力ファイルを実行します.");
            Console.WriteLine("[config]  : 設定ファイルパスを指定します.");
            Console.WriteLine("[debug]   : デバッグビルドする際は指定します.");
        }

        static private string[] CollectSources(string path)
        {
            return Directory.GetFiles(path, "*.c", SearchOption.AllDirectories);
        }

        static string CreateDefines(BuildConfig config)
        {
            if (config.Defines == null || config.Defines.Count == 0)
            { return ""; }

            var builder = new StringBuilder();
            var appendSpace = false;
            foreach(var def in config.Defines)
            {
                if (appendSpace)
                { builder.Append(" "); }

                builder.Append($"-D{def}");
                if (!appendSpace)
                { appendSpace = true; }
            }
            return builder.ToString();
        }

        static string CreateIncludeDirs(BuildConfig config)
        {
            if (config.IncludeDirs == null || config.IncludeDirs.Count == 0)
            { return ""; }

            var builder = new StringBuilder();
            var appendSpace = false;
            foreach(var inc in config.IncludeDirs)
            {
                if (appendSpace)
                { builder.Append(" "); }

                var path = CorrectPath(inc);

                builder.Append($"-I{path}");
                if (!appendSpace)
                { appendSpace = true; }
            }
            return builder.ToString();
        }

        static bool CreateNinjaFile(BuildConfig config, string[] files)
        {
            if (files.Length == 0)
                return false;

            var sources  = new StringBuilder();
            var builder  = new StringBuilder();
            var defines  = CreateDefines(config);
            var includes = CreateIncludeDirs(config);
            var debugFlg = config.Debug ? "debug" : "";

            var lccPath = CorrectPath(config.CompilerPath);
            builder.AppendLine($"lcc = {lccPath}");
            builder.AppendLine($"lcc_flags = {config.CompileOption}");
            builder.AppendLine($"defines = {defines}");
            builder.AppendLine($"include_dirs = {includes}");
            builder.AppendLine($"configuration = {debugFlg}");
            builder.AppendLine("rule compile");
            builder.AppendLine("    command = $lcc $lcc_flags $defines $include_dirs $configuration -c $in -o $out");
            builder.AppendLine("rule link");
            builder.AppendLine("    command = $lcc $lcc_flags -o $out $in");
            builder.AppendLine($"# Compile {files.Length} Files.");
            foreach(var srcPath in files)
            {
                var srcName = CorrectPath(srcPath);
                var objName = GetObjectPath(srcPath, config);
                sources.Append(objName + " ");
                builder.AppendLine($"build {objName}: compile {srcName}");
            }
            builder.AppendLine("# Link");
            builder.AppendLine($"build {config.TargetName}: link {sources}");

            var outputDir = Path.GetFullPath(config.OutputDir);
            var buildNinjaPath = Path.Combine(outputDir, "build.ninja");
            using var file = File.Create(buildNinjaPath);
            using var stream = new StreamWriter(file, Encoding.ASCII);
            stream.Write(builder.ToString());

            return true;
        }

        static string CorrectPath(string path)
        {
            var p = Path.GetFullPath(path);
            p = p.ToLower();
            p = p.Replace(":\\", "$:\\");
            return p;
        }

        static string GetObjectPath(string path, BuildConfig config)
        {
            var objName   = Path.GetFullPath(path);
            var inputDir  = Path.GetFullPath(config.InputDir) + "\\";
            var outputDir = Path.GetFullPath(config.OutputDir) + "\\";
            objName = objName.Replace(inputDir, outputDir);
            objName = Path.ChangeExtension(objName, ".o");
            return CorrectPath(objName);
        }
    }

}
