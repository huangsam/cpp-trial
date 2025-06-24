#!/bin/bash

# clang_tidy_wrapper.sh
# This script acts as an intermediary to control when clang-tidy is executed by CMake.
# It parses arguments passed by CMake's __run_co_compile to correctly identify
# the source file, clang-tidy executable, its arguments, and the compiler arguments,
# allowing specific files (like third-party libraries) to be skipped.

# Initialize variables to store parsed arguments
ACTUAL_CLANG_TIDY_EXEC="" # This will be the actual clang-tidy path
SOURCE_FILE="" # This will store the path of the source file being compiled
CLANG_TIDY_ARGS=() # Arguments specifically for clang-tidy (before --)
COMPILER_ARGS=() # Arguments specifically for the compiler (after --)

DELIMITER_FOUND=false

# The first argument to the wrapper script is the clang-tidy executable itself,
# as specified in CMAKE_CXX_CLANG_TIDY's second element.
ACTUAL_CLANG_TIDY_EXEC="$1"
shift # Remove the clang-tidy executable from the arguments list, now $@ starts with its args

# Parse the remaining arguments passed to the wrapper script
for arg in "$@"; do
    if [[ "$arg" == "--" ]]; then
        # This is the delimiter between clang-tidy args and compiler args
        DELIMITER_FOUND=true
    elif ! $DELIMITER_FOUND ; then
        # Arguments before the '--' delimiter are for clang-tidy
        # Heuristic to identify the SOURCE_FILE among clang-tidy's direct arguments:
        # It's usually a path ending with a source extension, is a file, and not a flag.
        if [[ "$arg" =~ \.(cpp|cc|cxx|c|m|mm)$ ]] && [[ -f "$arg" ]] && [[ ! "$arg" =~ ^- ]]; then
            SOURCE_FILE="$arg" # This is the main file being analyzed
        fi
        CLANG_TIDY_ARGS+=("$arg") # Always add to CLANG_TIDY_ARGS, as clang-tidy needs it
    else
        # Arguments after the '--' delimiter are for the compiler
        COMPILER_ARGS+=("$arg")
    fi
done

# Define patterns for source files to SKIP clang-tidy analysis
SKIP_PATTERNS=(
    "_deps/googletest-src/"
    # Add other patterns if you have more third-party libraries:
    # "third_party/some_library/"
)

SHOULD_SKIP=false
for pattern in "${SKIP_PATTERNS[@]}"; do
    if [[ "$SOURCE_FILE" == *"$pattern"* ]]; then
        SHOULD_SKIP=true
        break
    fi
done

if $SHOULD_SKIP; then
    echo "--> clang-tidy SKIPPED for: $SOURCE_FILE" >&2
    exec "${COMPILER_ARGS[@]}" # Execute the actual compiler command
else
    echo "--> Running clang-tidy for: $SOURCE_FILE" >&2
    # Execute clang-tidy with its arguments, followed by the delimiter,
    # and then the compiler arguments.
    exec "$ACTUAL_CLANG_TIDY_EXEC" "${CLANG_TIDY_ARGS[@]}" -- "${COMPILER_ARGS[@]}"
fi
