# Convenience wrapper around the CMake build and BEAST developer tools.
# CMakeLists.txt remains the source of truth for build targets and dependencies.

BUILD_DIR ?= build
BUILD_TYPE ?= Debug
BEAST_BUILD_APPS ?= ON
BEAST_BUILD_TESTS ?= ON
BEAST_BUILD_DOCS ?= OFF
CMAKE ?= cmake
CTEST ?= ctest
M4 ?= m4

# Metadata used by the M4 class generators. Values can be overridden on the
# make command line. Empty git values are handled by the generator scripts.
BEAST_AUTHOR ?= $(shell git config user.name 2>/dev/null)
BEAST_YEAR ?= $(shell date +%Y)
BEAST_REPOSITORY ?= $(shell git config --get remote.origin.url 2>/dev/null)
FORCE ?= 0

CMAKE_CONFIGURE_ARGS = \
	-S . \
	-B "$(BUILD_DIR)" \
	-DCMAKE_BUILD_TYPE="$(BUILD_TYPE)" \
	-DBEAST_BUILD_APPS="$(BEAST_BUILD_APPS)" \
	-DBEAST_BUILD_TESTS="$(BEAST_BUILD_TESTS)" \
	-DBEAST_BUILD_DOCS="$(BEAST_BUILD_DOCS)"

.PHONY: all configure build test docs clean distclean rebuild install \
	beast-estimator beast-model-info debug release \
	generate-cell-model generate-estimator help

all: build

configure:
	$(CMAKE) $(CMAKE_CONFIGURE_ARGS)

build: configure
	$(CMAKE) --build "$(BUILD_DIR)" --parallel

test: build
	$(CTEST) --test-dir "$(BUILD_DIR)" --output-on-failure

docs:
	$(MAKE) configure BEAST_BUILD_DOCS=ON
	$(CMAKE) --build "$(BUILD_DIR)" --target docs
	@printf '%s\n' \
		'Documentation generated:' \
		'  $(BUILD_DIR)/docs/html/index.html'

generate-cell-model:
	@test -n "$(NAME)" || { \
		echo 'Usage: make generate-cell-model NAME=<model-name>'; \
		exit 2; \
	}
	@M4="$(M4)" \
		BEAST_AUTHOR="$(BEAST_AUTHOR)" \
		BEAST_YEAR="$(BEAST_YEAR)" \
		BEAST_REPOSITORY="$(BEAST_REPOSITORY)" \
		FORCE="$(FORCE)" \
		./tools/generate_cell_model.sh "$(NAME)"

generate-estimator:
	@test -n "$(NAME)" || { \
		echo 'Usage: make generate-estimator NAME=<estimator-name>'; \
		exit 2; \
	}
	@M4="$(M4)" \
		BEAST_AUTHOR="$(BEAST_AUTHOR)" \
		BEAST_YEAR="$(BEAST_YEAR)" \
		BEAST_REPOSITORY="$(BEAST_REPOSITORY)" \
		FORCE="$(FORCE)" \
		./tools/generate_estimator.sh "$(NAME)"

beast-estimator: configure
	$(CMAKE) --build "$(BUILD_DIR)" --target beast-estimator --parallel

beast-model-info: configure
	$(CMAKE) --build "$(BUILD_DIR)" --target beast-model-info --parallel

install: build
	$(CMAKE) --install "$(BUILD_DIR)"

clean:
	@if [ -d "$(BUILD_DIR)" ]; then \
		$(CMAKE) --build "$(BUILD_DIR)" --target clean; \
	else \
		echo "Nothing to clean: $(BUILD_DIR) does not exist."; \
	fi

distclean:
	@if [ -d "$(BUILD_DIR)" ]; then \
		$(CMAKE) -E remove_directory "$(BUILD_DIR)"; \
	fi

rebuild: distclean build

debug:
	$(MAKE) build BUILD_TYPE=Debug

release:
	$(MAKE) build BUILD_TYPE=Release

help:
	@printf '%s\n' \
		'BEAST C++ build and developer-tool wrapper' \
		'' \
		'Usage:' \
		'  make                    Configure and build the project' \
		'  make configure          Configure CMake only' \
		'  make build              Configure and build all enabled targets' \
		'  make test               Build and run CTest' \
		'  make docs               Generate Doxygen HTML documentation' \
		'  make generate-cell-model NAME=R0R2C2' \
		'                          Generate CellModel_R0R2C2 .h/.cpp skeletons' \
		'  make generate-estimator NAME=UKF' \
		'                          Generate Estimator_UKF .h/.cpp skeletons' \
		'  make beast-estimator    Build only the estimator utility' \
		'  make beast-model-info   Build only the model-info utility' \
		'  make debug              Build with CMAKE_BUILD_TYPE=Debug' \
		'  make release            Build with CMAKE_BUILD_TYPE=Release' \
		'  make clean              Remove compiled files, keep CMake configuration' \
		'  make distclean          Remove the complete build directory' \
		'  make rebuild            Distclean and build again' \
		'  make install            Build and run cmake --install' \
		'  make help               Show this help' \
		'' \
		'Build variables:' \
		'  BUILD_DIR=build         CMake build directory' \
		'  BUILD_TYPE=Debug        CMake build type' \
		'  BEAST_BUILD_APPS=ON     Enable command-line utilities' \
		'  BEAST_BUILD_TESTS=ON    Enable tests' \
		'  BEAST_BUILD_DOCS=OFF    Enable the CMake Doxygen target' \
		'' \
		'Generator variables:' \
		'  M4=m4                   M4 executable' \
		'  BEAST_AUTHOR=<name>     Doxygen author (defaults to git user.name)' \
		'  BEAST_YEAR=<year>       Header year (defaults to current year)' \
		'  BEAST_REPOSITORY=<url>  Repository reference (defaults to git origin)' \
		'  FORCE=1                 Allow overwriting generated files' \
		'' \
		'Examples:' \
		'  make release' \
		'  make test BUILD_TYPE=Release' \
		'  make docs' \
		'  make generate-cell-model NAME=R0R2C2' \
		'  make generate-estimator NAME=UKF BEAST_AUTHOR="Jane Doe"' \
		'  make build BUILD_DIR=build-ci BEAST_BUILD_TESTS=OFF'
