#!/bin/bash
set -eu

mode="${1:-main}"

if [[ "$mode" == "main" ]]; then
    test -f ./build/bin/main.out && ./build/bin/main.out
elif [[ "$mode" == "test" ]]; then
    test -f ./build/bin/test.out && ./build/bin/test.out
else
    echo "Invalid mode: $mode. Please provide 'main' or 'test'"
    exit 1
fi
