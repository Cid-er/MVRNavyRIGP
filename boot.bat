@echo off
echo Select launch mode:
echo [1] Desktop
echo [2] VR
set /p choice="Enter choice: "

if "%choice%"=="1" start MVRNavyRIGP.exe -nohmd
if "%choice%"=="2" start MVRNavyRIGP.exe -vr