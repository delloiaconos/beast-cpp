# BEAST {#mainpage}

**Battery Estimation Architecture and Simulation Toolkit**

BEAST is a C++ framework for battery modeling, simulation, and state/parameter
estimation. The project is organized as a reusable library plus independent
command-line utilities.

## Project structure

- `include/beast/` — public library headers.
- `src/` — reusable BEAST implementation.
- `apps/` — independent command-line utilities, each with its own `main.cpp`.
- `tests/` — library and integration tests.
- `docs/` — user documentation and Doxygen configuration.

## Main components

- Battery cell models.
- State and parameter estimators.
- Numerical utilities.
- Runtime factories and estimator execution support.
- Standalone utilities linked against the BEAST library.

## Usage documentation

For detailed instructions covering configuration, builds, tests, utilities,
installation, and documentation generation, see [BEAST C++ Usage Guide](USAGE.md).

Generate the HTML documentation from the project root with:

```bash
make docs
```

The generated entry page is normally:

```text
build/docs/html/index.html
```

## License

BEAST is distributed under the GNU General Public License version 3.0.
See the repository `LICENSE` file for the complete license text.
