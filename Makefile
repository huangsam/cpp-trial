.PHONY: run test format build clean

run: build
	./build/bin/main.out

test: build
	./build/bin/test.out

format:
	find src test -name '*.cpp' -o -name '*.hpp' -exec clang-format --style="LLVM" -i {} +

# Step 1: set source and build, download GoogleTest, generate CMake assets
# Step 2: Run the build process and place binaries in build/bin
build:
	cmake -S . -B build
	cmake --build build

clean:
	rm -rf build
