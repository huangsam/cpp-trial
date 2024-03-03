#!/bin/bash
set -eux

# Download GoogleTest dependency and prepare make assets
cmake -S . -B build

# Run build process E2E and place final assets in build/ folder
cmake --build build
