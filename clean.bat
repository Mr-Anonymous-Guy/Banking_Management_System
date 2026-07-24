@echo off
echo [INFO] Cleaning build directory...
if exist "build" (
    rmdir /s /q build
    echo [SUCCESS] Clean completed.
) else (
    echo [INFO] Nothing to clean.
)
pause
