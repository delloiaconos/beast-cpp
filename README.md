# BEAST C++

**BEAST — Battery Estimation Architecture and Simulation Toolkit**

`beast-cpp` is the C++ implementation of BEAST, a framework for battery modeling,
simulation, and state/parameter estimation. The repository is organized around a
reusable C++ library plus independent command-line utilities that link against it.

The equivalent Python implementation is maintained separately as `beast-py`.

## Repository structure

```text
beast-cpp/
├── include/beast/   Public library headers
├── src/             Reusable BEAST implementation
├── apps/            Independent command-line utilities
├── tests/           Library and integration tests
├── docs/            User and Doxygen documentation
├── CMakeLists.txt   CMake project definition
└── Makefile         Convenience wrapper around CMake
```

A central project rule is that `src/` contains reusable library code and no
application entry points. Each utility owns its `main.cpp` under `apps/` and
links against the `beast` library.

## Requirements

The project requires:

- a C++17-compatible compiler;
- CMake 3.16 or newer.

For the convenience commands shown below, GNU Make or a compatible `make`
implementation is also expected. Doxygen is optional and is required only when
generating the API documentation.

## Quick start

Configure and build the project from the repository root:

```bash
make
```

Build and run the tests:

```bash
make test
```

Build a release configuration:

```bash
make release
```

The Makefile is only a developer-friendly front end. CMake remains the source
of truth for targets, dependencies, and installation rules.

## Utilities

The current command-line applications are:

- `beast-estimator` — runs the battery estimation workflow;
- `beast-model-info` — reports the cell models and estimators registered by BEAST.

After a default build, executables are generated in the selected CMake build
directory, normally `build/`.

## Documentation

Detailed build, execution, testing, installation, and documentation instructions
are available in [docs/USAGE.md](docs/USAGE.md).

Generate the Doxygen documentation with:

```bash
make docs
```

The generated HTML entry point is normally:

```text
build/docs/html/index.html
```

## License

BEAST is distributed under the **GNU General Public License version 3.0**.
See [LICENSE](LICENSE) for the complete license text.
