# Convenience wrapper around the CMake build.
# CMakeLists.txt remains the source of truth for build targets and dependencies.

BUILD_DIR ?= build
BUILD_TYPE ?= Debug
BEAST_BUILD_APPS ?= ON
BEAST_BUILD_TESTS ?= ON
BEAST_BUILD_DOCS ?= OFF
CMAKE ?= cmake
CTEST ?= ctest

CMAKE_CONFIGURE_ARGS = \
	-S . \
	-B "$(BUILD_DIR)" \
	-DCMAKE_BUILD_TYPE="$(BUILD_TYPE)" \
	-DBEAST_BUILD_APPS="$(BEAST_BUILD_APPS)" \
	-DBEAST_BUILD_TESTS="$(BEAST_BUILD_TESTS)" \
	-DBEAST_BUILD_DOCS="$(BEAST_BUILD_DOCS)"

.PHONY: all configure build test docs clean distclean rebuild install \
	beast-estimator beast-model-info debug release help

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
		'BEAST C++ build wrapper' \
		'' \
		'Usage:' \
		'  make                    Configure and build the project' \
		'  make configure          Configure CMake only' \
		'  make build              Configure and build all enabled targets' \
		'  make test               Build and run CTest' \
		'  make docs               Generate Doxygen HTML documentation' \
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
		'Variables:' \
		'  BUILD_DIR=build         CMake build directory' \
		'  BUILD_TYPE=Debug        CMake build type' \
		'  BEAST_BUILD_APPS=ON     Enable command-line utilities' \
		'  BEAST_BUILD_TESTS=ON    Enable tests' \
		'  BEAST_BUILD_DOCS=OFF    Enable the CMake Doxygen target' \
		'' \
		'Examples:' \
		'  make release' \
		'  make test BUILD_TYPE=Release' \
		'  make docs' \
		'  make docs BUILD_DIR=build-docs' \
		'  make build BUILD_DIR=build-ci BEAST_BUILD_TESTS=OFF'
