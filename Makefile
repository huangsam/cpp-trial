# For more about phony targets:
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
# https://stackoverflow.com/a/2145605/2748860
.PHONY: run test

# Define all build dependencies
SRC_FILES := $(wildcard src/*.cpp src/*.hpp)
TEST_FILES := $(wildcard test/*.cpp test/*.hpp)
BUILD_DEPS := $(SRC_FILES) $(TEST_FILES)

# This Makefile runs and tests a C++ project using CMake and GoogleTest.
# The build artifacts will be placed in the build directory.
all: run test

run: build
	./build/bin/main.out

test: build
	./build/bin/test.out

# Step 1: Set source and build, download GoogleTest, generate CMake assets
# Step 2: Run the build process and place binaries in build/bin
build: $(BUILD_DEPS)
	cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -G Ninja
	cmake --build build

# Install required software:
# https://formulae.brew.sh/formula/clang-format
# https://formulae.brew.sh/formula/cmake
# https://formulae.brew.sh/formula/cppcheck
# https://formulae.brew.sh/formula/ninja
setup:
	brew install --formula clang-format cmake cppcheck ninja

# Choose formatting style based on preferences:
# https://clang.llvm.org/docs/ClangFormatStyleOptions.html#basedonstyle
format:
	clang-format -i $(BUILD_DEPS)

# Lint the entire codebase
# https://cppcheck.sourceforge.io/
lint:
	cppcheck ./src ./test

clean:
	rm -rf build
