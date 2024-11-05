#!/bin/bash
set -eux

if [[ ! -f ./build/bin/main.out ]]; then
    exit 1
fi

./build/bin/main.out
