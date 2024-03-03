#!/bin/bash
set -eux

# Possible options include:
# LLVM, GNU, Google, Chromium, Microsoft, Mozilla, WebKit
PREFERRED_STYLE="Google"

find src test -name '*.cpp' -exec clang-format --style="$PREFERRED_STYLE" -i {} +
find src test -name '*.h'  -exec clang-format --style="$PREFERRED_STYLE" -i {} +
