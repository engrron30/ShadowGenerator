#!/bin/bash

# this script prepares the Raylib code in Package directory.
# Only run when executing in Linux
# No need to run if you have Raylib already in your machine

RAYLIB_HEADER_GLOBAL="/usr/include/raylib.h"
RAYLIB_HEADER_LOCAL="./raylib/src/raylib.h"
REPO_URL="https://github.com/raysan5/raylib"
LOCAL_DIR="raylib"

# Check for global raylib
if [ -f "$RAYLIB_HEADER_GLOBAL" ]; then
    echo "raylib is installed globally at $RAYLIB_HEADER_GLOBAL"
    exit 0
fi

# Check for local raylib
if [ -f "$RAYLIB_HEADER_LOCAL" ]; then
    echo "raylib already exists locally at $RAYLIB_HEADER_LOCAL"
    exit 0
fi

# Not installed, install locally
echo "raylib not found. Installing locally..."

# Clone the repository
if [ -d "$LOCAL_DIR" ]; then
    echo "Existing '$LOCAL_DIR' directory found. Skipping clone."
else
    git clone "$REPO_URL" "$LOCAL_DIR"
    if [ $? -ne 0 ]; then
        echo "Failed to clone raylib."
        exit 1
    fi
fi

# Build raylib locally
echo "🔧 Building raylib locally..."
cd "$LOCAL_DIR" || exit
make PLATFORM=PLATFORM_DESKTOP
BUILD_RESULT=$?
cd ..

# Final check
if [ $BUILD_RESULT -eq 0 ]; then
    echo "raylib built locally in '$LOCAL_DIR'."
else
    echo "Failed to build raylib."
    exit 1
fi

