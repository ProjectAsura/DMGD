@echo off
set WORK_PATH=%~dp0
set SASUKE=%DMGD_ROOT%tools\sasuke\bin\Release\netcoreapp3.1\sasuke.exe
call %SASUKE% %1 %WORK_PATH%config.json
