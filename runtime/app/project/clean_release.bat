@echo off
cd /d %~dp0
rmdir /s /q "..\\bin\\release"
del /q ".\\.ninja_log"
