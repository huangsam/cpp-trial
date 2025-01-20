.PHONY: run test format build clean

run: build
	./build/bin/main.out

test: build
	./build/bin/test.out

format:
	find src test -name '*.cpp' -o -name '*.hpp' -exec clang-format --style="LLVM" -i {} +

build:
	bash ./build.sh

clean:
	rm -rf build
