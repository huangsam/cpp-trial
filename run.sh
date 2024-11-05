#!/bin/bash
set -eux

if [[ ! -f ./build/bin/main.out ]]; then
    exit 1
fi

# Run binary after E2E build
./build/bin/main.out
