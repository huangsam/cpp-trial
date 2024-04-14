#!/bin/bash
set -eux

MAIN_PATH="./build/bin/main.out"

# Run the executable if it exists
[[ -f "$MAIN_PATH" ]] && "$MAIN_PATH"
