#!/bin/bash
set -eux

# Run the following:
# - Set source directory to current one
# - Set build directory to ./build
# - Download GoogleTest dependency
# - Generate CMake assets for E2E build
cmake -S . -B build

# Run E2E build and place output artifacts in ./build
cmake --build build
