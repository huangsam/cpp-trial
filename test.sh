#!/bin/bash
set -eux

ctest --test-dir build/test --output-on-failure
