@echo off
call build.bat
if %errorlevel% neq 0 exit /b %errorlevel%

cls
echo ========================================
echo  Launching application...
echo ========================================
echo.

.\build\banking_system.exe

echo.
echo ========================================
echo  Application terminated.
echo ========================================
pause
