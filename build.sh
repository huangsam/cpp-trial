#!/bin/bash
set -eu

# Download GoogleTest dependency and prepare make assets
cmake -S . -B build

# Run build process E2E and place final assets in build/ folder
cmake --build build

echo 'Build complete. You can "cd build && ctest" now'
