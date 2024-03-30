using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace sasuke
{
    public class BuildConfig
    {
        /// <summary>
        /// Ninja.exe へのfileパス.
        /// </summary>
        [JsonPropertyName("ninja_path")]
        public string NinjaPath { get; set; }

        /// <summary>
        /// ソースコードのルートディレクトリの指定.
        /// </summary>
        [JsonPropertyName("input_dir")]
        public string InputDir { get; set; }

        /// <summary>
        /// 出力ディレクトリの指定.
        /// </summary>
        [JsonPropertyName("output_dir")]
        public string OutputDir { get; set; }

        /// <summary>
        /// 出力ファイル名の指定.
        /// </summary>
        [JsonPropertyName("target_name")]
        public string TargetName { get; set; }

        /// <summary>
        /// bgb エミュレーターへのfileパス.
        /// </summary>
        [JsonPropertyName("emulator_path")]
        public string EmulatorPath { get; set; }

        /// <summary>
        /// gbdk/bin が配置されているパス.
        /// </summary>
        [JsonPropertyName("compiler_path")]
        public string CompilerPath { get; set; }

        /// <summary>
        /// コンパイルオプション.
        /// </summary>
        [JsonPropertyName("compile_option")]
        public string CompileOption { get; set; }

        /// <summary>
        /// プリプロセッサ定義.
        /// </summary>
        [JsonPropertyName("defines")]
        public List<string> Defines { get; set; }

        /// <summary>
        /// 入力ディレクトリ.
        /// </summary>
        [JsonPropertyName("include_dirs")]
        public List<string> IncludeDirs { get; set; }

        /// <summary>
        /// デバッグビルドフラグ.
        /// </summary>
        public bool Debug { get; set; }
    }
}
