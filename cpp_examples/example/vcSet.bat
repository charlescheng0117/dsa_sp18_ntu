@echo off & if defined debug echo on

if %1.==. (
	echo Usage: %~nx0 version
	echo 	^(version = 6, 8, 9, 10, 9_64, 9_32for64^)
	echo 	6: VS 6.0
	echo 	8: VS 8.0
	echo 	9: VS 9.0, 32 bit ^(編譯32位元執行檔，32 ^& 64 bit 平台均可執行^)
	echo 	10: VS 10.0
	echo 	11: VS 11.0
	echo 	14: VS 14.0
	echo 	9_64: VS 9.0, 64 bit ^(編譯64位元執行檔，只有 64 bit 平台可執行^)
	echo 	9_32for64: VS 9.0 ^(在32位元環境下編譯64位元執行檔，32 ^& 64 bit 平台均可執行 if compiled over a 64bit platform^)
	exit /b
)



if %1==6 (
	echo Set VC version to %1
rem	call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
	call "C:\Program Files (x86)\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
	exit /b
)
if %1==8 (
	echo Set VC version to %1
rem	call "C:\Program Files\Microsoft Visual Studio 8\VC\Bin\vcvars32.bat"
	call "C:\Program Files (x86)\Microsoft Visual Studio 8\VC\Bin\vcvars32.bat"
	exit /b
)
if %1==9 (
	echo Set VC version to %1
rem	call "C:\Program Files\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"
rem	call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"
	exit /b
)
if %1==10 (
	echo Set VC version to %1
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat"
	exit /b
)
if %1==11 (
	echo Set VC version to %1
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 11.0\VC\bin\vcvars32.bat"
rem	call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
	exit /b
)
if %1==14 (
	echo Set VC version to %1
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat"
	exit /b
)
if %1==9_64 (
	echo Set VC version to %1
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\bin\amd64\vcvarsamd64.bat"
	exit /b
)
if %1==9_32for64 (
	echo Set VC version to %1
	call "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\bin\x86_amd64\vcvarsx86_amd64.bat"
	exit /b
)

echo Unknown VC version: %1