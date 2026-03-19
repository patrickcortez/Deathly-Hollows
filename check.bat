@echo off

:: This script is used to compile the game once done, I'm tired of manually typing the long ass ompilation commands

echo Checking g++ 

:: Check gcc, if not availabe then we warn the dev.

g++ --version >nul 2>&1 

if %ERRORLEVEL% EQU 0 (

    echo Compiling main.cpp...

    g++ src/main.cpp -o bin/Desp.exe >nul 2>&1

    echo Compiling Done!
    
) else (
    echo Failed Compilation
)