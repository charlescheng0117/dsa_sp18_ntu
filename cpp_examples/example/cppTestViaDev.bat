@echo off

if %1.==. (
        echo Usage: %0 mainNameOfCppFile
        exit /b
)

del %1.exe
echo ====== Compiling %1.cpp via g++:
g++ %1.cpp -o %1
rem g++ %1.cpp -std=c++11 -O2 -o %1
echo ====== Running %1.exe:
%1.exe