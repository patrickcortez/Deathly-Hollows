@echo off

echo checking git version...

git --version >nul 2>&1

if %ERRORLEVEL% EQU 0 (

    if %1 == "" (
    echo Commit Message is empty!
    ) else (
    :: Stage once theres a commit message
    git add -A
    ::silently commit 
    git commit -m %1 >nul 2>&1

    echo Committed to repo
    )
) else (
    echo Git not found!
)