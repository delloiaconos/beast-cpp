# BEAST C++ Usage Guide

This document describes how to configure, build, test, run, install, and
extend the C++ implementation of **BEAST — Battery Estimation Architecture and
Simulation Toolkit**.

## 1. Prerequisites

A normal BEAST build requires:

- a C++17-compatible compiler;
- CMake 3.16 or newer.

The top-level convenience `Makefile` additionally requires `make`.

Doxygen is optional and is needed only for `make docs` or the CMake `docs`
target.

## 2. Build with the top-level Makefile

For day-to-day development, use the Makefile from the repository root. It wraps
CMake and does not duplicate the CMake target definitions.

### Default build

```bash
make
```

This is equivalent to:

```bash
make build
```

By default the project is configured in `build/` using the `Debug` build type,
with command-line applications and tests enabled.

### Debug and release builds

```bash
make debug
make release
```

### Build a specific utility

```bash
make beast-estimator
make beast-model-info
```

### Rebuild and clean

Remove compiled files while retaining the CMake configuration:

```bash
make clean
```

Remove the complete build directory:

```bash
make distclean
```

Recreate the build from scratch:

```bash
make rebuild
```

### Makefile configuration variables

The wrapper accepts variables on the command line:

```text
BUILD_DIR             CMake build directory       default: build
BUILD_TYPE            CMake build type            default: Debug
BEAST_BUILD_APPS      Build command-line tools    default: ON
BEAST_BUILD_TESTS     Build tests                 default: ON
BEAST_BUILD_DOCS      Enable Doxygen target       default: OFF
```

Examples:

```bash
make build BUILD_TYPE=Release
make build BUILD_DIR=build-release BUILD_TYPE=Release
make build BEAST_BUILD_TESTS=OFF
make build BUILD_DIR=build-lib BEAST_BUILD_APPS=OFF BEAST_BUILD_TESTS=OFF
```

Display the complete Makefile command reference with:

```bash
make help
```

## 3. Build with CMake directly

The Makefile is optional. The project can be configured directly with CMake:

```bash
cmake -S . -B build
cmake --build build --parallel
```

Run the tests with:

```bash
ctest --test-dir build --output-on-failure
```

A release configuration can be requested with:

```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel
```

### CMake project options

The project currently provides these options:

```text
BEAST_BUILD_APPS   Build BEAST command-line utilities
BEAST_BUILD_TESTS  Build BEAST tests
BEAST_BUILD_DOCS   Enable the Doxygen documentation target
```

For example, to build only the reusable library:

```bash
cmake -S . -B build-lib \
  -DBEAST_BUILD_APPS=OFF \
  -DBEAST_BUILD_TESTS=OFF
cmake --build build-lib --parallel
```

## 4. Run the estimator utility

After a default build, run the estimator application as follows:

```bash
./build/beast-estimator \
  -i <experiment-input-dir> \
  -o <output-dir> \
  -m R0R1C1 \
  -e EKFDUAL \
  -d <model-data-dir>
```

The options select:

- `-i` — experiment input directory;
- `-o` — output directory;
- `-m` — cell-model name;
- `-e` — estimator name;
- `-d` — model-data directory.

### Experiment input files

The experiment input directory must contain:

```text
MD_t_all.in
MD_u_all.in
MD_yXP_all.in
```

### Model-data files

The model-data directory must contain the files required by the selected legacy
cell-model implementation. The current estimator workflow validates the
following common model inputs:

```text
MD_x0.in
MD_p0.in
MD_COV_sxWvec.in
MD_COV_sxVvec.in
MD_COV_spRvec.in
MD_COV_spEvec.in
MD_pfix_Qn_Ah.in
MD_pfix_eta.in
MD_pfix_soc.in
MD_pfix_ocv0.in
MD_pfix_ocv1.in
```

Results are written to the directory selected with `-o`.

## 5. Inspect available models and estimators

The `beast-model-info` utility demonstrates an independent application linked
against the same BEAST library. Run it with:

```bash
./build/beast-model-info
```

Use this utility to inspect the models and estimators currently exposed by the
runtime factories.

## 6. Run tests

Using the Makefile:

```bash
make test
```

Using CMake/CTest directly:

```bash
cmake -S . -B build -DBEAST_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## 7. Generate Doxygen documentation

Doxygen support is optional and is disabled during a normal build.

Using the Makefile:

```bash
make docs
```

The command configures CMake with `BEAST_BUILD_DOCS=ON` and builds the `docs`
target. The generated HTML documentation is written to:

```text
build/docs/html/index.html
```

A separate documentation build directory can be used:

```bash
make docs BUILD_DIR=build-docs
```

The corresponding entry page is then:

```text
build-docs/docs/html/index.html
```

Using CMake directly:

```bash
cmake -S . -B build-docs -DBEAST_BUILD_DOCS=ON
cmake --build build-docs --target docs
```

If Doxygen is not installed, normal BEAST builds remain available; only the
documentation-enabled configuration requires it.

## 8. Install the library

Using the Makefile:

```bash
make install
```

Or directly with CMake:

```bash
cmake --install build
```

A custom installation prefix can be selected during configuration, for example:

```bash
cmake -S . -B build-release \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build build-release --parallel
cmake --install build-release
```

The CMake installation exports the BEAST library target and installs the public
headers from `include/`.

## 9. Add a new command-line utility

Each independent application belongs under `apps/` and owns its own `main.cpp`.
For example:

```text
apps/my-tool/main.cpp
```

Add the executable to `CMakeLists.txt` and link it against the reusable library:

```cmake
add_executable(beast-my-tool
    apps/my-tool/main.cpp
)

target_link_libraries(beast-my-tool
    PRIVATE beast::beast
)
```

No new `main()` function should be added under `src/`. The `src/` tree is
reserved for reusable library implementation.

If the utility is intended to be part of the standard application set, place
its CMake definition inside the existing `BEAST_BUILD_APPS` section.

## 10. Project organization rule

The repository follows this separation:

```text
include/beast/   Public BEAST API
src/             Reusable library implementation
apps/            Independent executable entry points
tests/           Tests
docs/            User and generated-documentation sources
```

The intended dependency direction is:

```text
BEAST library
    |
    +-- beast-estimator
    +-- beast-model-info
    +-- future utilities
```

Applications may depend on the BEAST library. The BEAST library must not depend
on application-specific `main.cpp` files.

## 11. Further documentation

- `README.md` — repository overview and quick start;
- `MIGRATION.md` — architectural changes from the original project layout;
- `docs/mainpage.md` — Doxygen landing page;
- `docs/Doxyfile.in` — Doxygen configuration template.
