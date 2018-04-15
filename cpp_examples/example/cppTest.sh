#!/bin/bash

if [ $# -eq 0 ]; then
    echo Usage: bash $0 mainNameOfCppFile
	exit
fi

echo ====== Compiling $1.cpp via g++:
g++ $1.cpp -o $1
echo ====== Testing $1:
./$1