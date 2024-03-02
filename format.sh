#!/bin/bash
set -eux

# Possible options include:
# LLVM, GNU, Google, Chromium, Microsoft, Mozilla, WebKit
PREFERRED_STYLE="Google"

find . -name '*.cpp' -exec clang-format --style="$PREFERRED_STYLE" -i {} +
find . -name '*.h'  -exec clang-format --style="$PREFERRED_STYLE" -i {} +
