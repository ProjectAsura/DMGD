using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace sasuke
{
    public class BuildConfig
    {
        [JsonPropertyName("NinjaPath")]
        public string NinjaPath { get; set; }

        [JsonPropertyName("InputDir")]
        public string InputDir { get; set; }

        [JsonPropertyName("OutputDir")]
        public string OutputDir { get; set; }

        [JsonPropertyName("OutputName")]
        public string OutputName { get; set; }

        [JsonPropertyName("EmulatorPath")]
        public string EmulatorPath { get; set; }

        [JsonPropertyName("CompilerPath")]
        public string CompilerPath { get; set; }

        [JsonPropertyName("CompileOption")]
        public string CompileOption { get; set; }
    }
}
