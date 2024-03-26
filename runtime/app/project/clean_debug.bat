@echo off
cd /d %~dp0
rmdir /s /q "..\\bin\\debug"
del /q ".\\.ninja_log"
