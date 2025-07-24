#!/bin/bash

# This script prepare the CMake needed for compiling the Raylib.
# Current script downloads CMake Version 3.29.3.
# Current Raylib code needs CMake with version 3.2 and up.

wget https://github.com/Kitware/CMake/releases/download/v3.29.3/cmake-3.29.3-linux-x86_64.tar.gz
tar -xzf cmake-3.29.3-linux-x86_64.tar.gz
