#!/bin/bash
# run.sh - Compile and run the Banking Management System

echo "Compiling the Banking Management System..."
make

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the application..."
    ./build/banking_system.exe
else
    echo "Compilation failed!"
    exit 1
fi
