@echo off
cd /d %~dp0
set ROOT_PATH=%~dp0
call "../../../tools/collector/bin/Release/collector.exe" "../src" "../bin" sample.gb "./rule.ninja"
call "../../../external/ninja/ninja.exe" -v -f ..\bin\build.ninja
pause