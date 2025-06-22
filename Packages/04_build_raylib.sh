#!/bin/bash

# Exit on error
set -e

# Get absolute path of script directory
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Add local CMake to PATH
export PATH="$SCRIPT_DIR/cmake-3.29.3-linux-x86_64/bin:$PATH"

# Navigate to raylib folder
cd "$SCRIPT_DIR/raylib"

# Create build directory
mkdir -p build
cd build

# Run CMake and build
cmake ..
make

