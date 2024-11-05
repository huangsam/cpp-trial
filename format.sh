#!/bin/bash
set -eux

# Possible options include:
# LLVM, GNU, Google, Chromium, Microsoft, Mozilla, WebKit
STYLE="LLVM"

find src test \
    -name '*.cpp' -o -name '*.h' \
    -exec clang-format --style="$STYLE" -i {} +
