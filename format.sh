#!/bin/bash
set -eu

# Possible options include:
# LLVM, GNU, Google, Chromium, Microsoft, Mozilla, WebKit
clang-format --style=Google -i *.cpp *.h
