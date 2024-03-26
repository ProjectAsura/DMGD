@echo off
cd /d %~dp0
set ROOT_PATH=%~dp0
set OUT_DIR="../bin/debug"
call "../../../tools/collector/bin/Release/collector.exe" "../src" %OUT_DIR% app.gb "./rule.ninja"
call "../../../external/ninja/ninja.exe" -v -f %OUT_DIR%\build.ninja
pause