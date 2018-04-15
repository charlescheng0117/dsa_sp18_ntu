@echo off

if %1.==. (
        echo Usage: %0 mainNameOfCppFile
        exit /b
)

if exist %1.exe (
	echo ====== Deleting %1.exe
	del %1.exe
)
echo ====== Compiling %1.cpp via VC:
cl %1.cpp /nologo /EHsc
del %1.obj
echo ====== Running %1.exe:
%1.exe

