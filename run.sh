#!/bin/bash

echo "🔧 Compiling stack_demo..."
mkdir -p bin
g++ -Wall -std=c++17 -o bin/stack_demo src/stack_demo.cpp

if [ $? -eq 0 ]; then
    echo "✅ Compiled successfully!"
    echo ""
    echo "🚀 Running stack_demo..."
    echo "─────────────────────────────"
    ./bin/stack_demo
    echo "─────────────────────────────"
    echo "✅ Done!"
else
    echo "❌ Compilation failed. Check the errors above."
fi
