#!/bin/bash
set -eux

if [ ! -f build/test ]; then
    echo -n "Cannot find tests. Please run build.sh first"
    exit 1
fi

# Run tests after E2E build
ctest --test-dir build/test --output-on-failure
