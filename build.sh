#!/bin/bash
set -eux

# Run the following:
# - Set source directory to ./
# - Set build directory to ./build
# - Download GoogleTest dependency
# - Generate CMake assets for E2E build
cmake -S . -B build

# Run the following:
# - E2E build process
# - Place binary assets in ./build
cmake --build build
