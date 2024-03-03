# CPP Trial

Coding in C++ to explore tools like [CMake](https://cmake.org/) and [GoogleTest](https://google.github.io/googletest/).

## Getting started

Please install tools like `cmake` and `clang-format` first beforehand. YOu can do this with Homebrew on Mac by running `brew install cmake clang-format`.

Once all the tool requirements are met, you can run the end-to-end build process:

```shell
bash build.sh
```

From there, run the binaries from the `build/bin` folder.

```shell
./build/bin/main.out # for main executable
./build/bin/test.out # for GoogleTest executable
```

### Testing the code

If you wish to use `ctest` for testing, run:

```shell
ctest --test-dir build/test
```

### Formatting the code

If you wish to reformat the code, run:

```shell
bash format.sh
```
