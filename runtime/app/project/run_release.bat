@echo off
cd /d %~dp0
set OUT_DIR="..\\bin\\release"
call "../../../external/bgb/bgb64.exe" -rom %OUT_DIR%\app.gb
