#!/bin/sh
set -eu

# Install required software:
# https://formulae.brew.sh/formula/clang-format
# https://formulae.brew.sh/formula/cmake
# https://formulae.brew.sh/formula/cppcheck
# https://formulae.brew.sh/formula/ninja
brew install --formula clang-format cmake cppcheck ninja
