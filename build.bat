@echo off
echo ========================================
echo  Building Project...
echo ========================================

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] g++ compiler not found!
    echo Please install MinGW or ensure g++ is in your system PATH.
    pause
    exit /b 1
)

if not exist "build" mkdir build

echo [INFO] Compiling source files...
where make >nul 2>nul
if %errorlevel% equ 0 (
    make
) else (
    where mingw32-make >nul 2>nul
    if %errorlevel% equ 0 (
        mingw32-make
    ) else (
        echo [INFO] Make not found. Falling back to direct g++ compilation...
        g++ -std=c++17 -Wall -Wextra -Iinclude src\*.cpp -o build\banking_system.exe
    )
)

if %errorlevel% neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

echo [SUCCESS] Build completed.
exit /b 0
