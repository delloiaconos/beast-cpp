# beast-cpp

BEAST: Battery Estimation Algorithms Software Toolkit, C++ implementation.

## Project layout

```text
include/beast/          Public library headers
src/                    Reusable BEAST implementation (no main functions)
  common/
  numerics/
  cell_models/
  estimators/
  runtime/
apps/                   Independent command-line utilities
  estimator/
  model-info/
tests/                  Library tests
```

The central rule is that `src/` builds **libbeast**. Every command-line utility has its own
`main.cpp` under `apps/` and links to the library. This allows any number of utilities without
mixing application entry points into reusable code.

## Build

A top-level `Makefile` wraps the CMake workflow for day-to-day development. CMake remains the source of truth for targets and dependencies.

```bash
make          # configure and build
make test     # build and run tests
make release  # Release build
make clean    # clean compiled files
make rebuild  # recreate the build from scratch
make help     # list all wrapper targets and variables
```

You can invoke CMake directly when needed:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The Makefile accepts build overrides, for example:

```bash
make build BUILD_TYPE=Release BUILD_DIR=build-release
make build BEAST_BUILD_TESTS=OFF
```

Generated utilities:

- `beast-estimator` - runs the estimator workflow that was previously implemented by `src/main.cpp` and `src/EstimatorLoop.cpp`.
- `beast-model-info` - prints the cell models and estimators registered by the runtime factories; it also demonstrates a second independent `main`.

## Estimator utility

```bash
./build/beast-estimator \
  -i <experiment-input-dir> \
  -o <output-dir> \
  -m R0R1C1 \
  -e EKFDUAL \
  -d <model-data-dir>
```

Required experiment files:

- `MD_t_all.in`
- `MD_u_all.in`
- `MD_yXP_all.in`

Required model files:

- `MD_x0.in`
- `MD_p0.in`
- `MD_COV_sxWvec.in`
- `MD_COV_sxVvec.in`
- `MD_COV_spRvec.in`
- `MD_COV_spEvec.in`
- `MD_pfix_Qn_Ah.in`
- `MD_pfix_eta.in`
- `MD_pfix_soc.in`
- `MD_pfix_ocv0.in`
- `MD_pfix_ocv1.in`

Outputs are written to the selected output directory.

## Add a new utility

Create a new entry point, for example:

```text
apps/my-tool/main.cpp
```

and add:

```cmake
add_executable(beast-my-tool apps/my-tool/main.cpp)
target_link_libraries(beast-my-tool PRIVATE beast::beast)
```

No changes to the library source tree are required just to add another `main`.

## Architectural changes from the original project

- Replaced `inc/` with a conventional `include/beast/` public include tree.
- Removed the library dependency on `main.h`.
- Moved estimator execution into `beast::run_estimator`.
- Added cell-model and estimator factories.
- Added `OPENLOOP` to runtime estimator selection.
- Removed the unused compile-time `CellModel_selection.h` and `Estimator_selection.h` mechanism.
- Replaced manual ownership in the estimator runner with RAII.
- Corrected exception catches to match exceptions thrown by value.
- Corrected the estimator input loop so EOF does not trigger one extra invalid estimator step.
- Corrected legacy `Matrix` array deallocation and assignment ownership issues.
- Added CMake targets for a reusable library and multiple executables.

## Compatibility note

The numerical, cell-model, and estimator algorithms remain the legacy implementation. The current
refactor intentionally focuses on project boundaries and build structure rather than rewriting the
algorithms. This makes it easier to compare behavior with the prior beast-cpp / beast-py code before
performing deeper modernization.
