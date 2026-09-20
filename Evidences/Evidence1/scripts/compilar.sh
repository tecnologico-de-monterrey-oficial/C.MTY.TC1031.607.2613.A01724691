#!/bin/bash
cd "$(dirname "$0")/.."
g++ -std=c++11 -O2 -Iinclude src/main.cpp -o build/evidencia1.exe
echo "Listo: build/evidencia1.exe"
