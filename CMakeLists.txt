cmake_minimum_required(VERSION 3.16)

project(beast-cpp VERSION 0.2.0 LANGUAGES C CXX)

option(BEAST_BUILD_APPS "Build BEAST command-line utilities" ON)
option(BEAST_BUILD_TESTS "Build BEAST tests" ON)
option(BEAST_BUILD_REGS "Build BEAST cpp/h/hpp files from registry and templates" OFF)
option(BEAST_BUILD_DOCS "Enable BEAST Doxygen documentation target" OFF)

file(GLOB CELL_MODEL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cell_models/CellModel_*.cpp"
)

file(GLOB ESTIMATOR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/estimators/Estimator_*.cpp"
)

add_library(beast
    src/common/Exception.cpp
    src/common/Debug.cpp

    src/numerics/Matrix.cpp
    src/numerics/Matrix_functions.cpp
    src/numerics/gaussj.cpp
    src/numerics/interpolation.c

    src/io/ModelDataLoader.cpp

    src/cell_models/CellModel.cpp
    ${CELL_MODEL_SOURCES}

    src/estimators/Estimator.cpp
    ${ESTIMATOR_SOURCES}

    src/runtime/cell_model_factory.cpp
    src/runtime/estimator_factory.cpp
    src/runtime/estimator_runner.cpp
)

add_library(beast::beast ALIAS beast)

target_include_directories(beast
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cell_models
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cell_models/Data
)

target_compile_features(beast PUBLIC cxx_std_17)
set_target_properties(beast PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES)

if(MSVC)
    target_compile_options(beast PRIVATE /W3)
else()
    target_compile_options(beast PRIVATE -Wall -Wextra -Wpedantic)
endif()


if(BEAST_BUILD_REGS)
    find_program(XMLLINT_BIN xmllint)
    if(NOT XMLLINT_BIN)
        message(FATAL_ERROR "xmllint utility not found! Please install libxml2-utils.")
    endif()

    find_program(FMPP_BIN ${CMAKE_CURRENT_SOURCE_DIR}/tools/fmpp/fmpp_0.9.16/bin/fmpp)
    if(NOT FMPP_BIN)
        message(FATAL_ERROR "FMPP not found! Ensure it is in your PATH.")
    endif()

    # Percorsi dei file
    set(XSD_FILE "${CMAKE_CURRENT_SOURCE_DIR}/architecture/beast-registry.xsd")
    set(XML_MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/architecture/beast-architecture.xml")
    set(OUTPUT_MARKER "${CMAKE_CURRENT_BINARY_DIR}/generated/beast_generated.cpp")

    # ==========================================
    # VALIDAZIONE XML (Target Manuale)
    # ==========================================
    add_custom_target(registry-validate
        COMMAND echo "Validating XML data structure..."
        COMMAND ${XMLLINT_BIN} --noent --schema ${XSD_FILE} ${XML_MAIN_FILE} --noout
        COMMENT "Checking XML schema validity"
    )

    # ==========================================
    # GENERAZIONE FMPP (Target Manuale)
    # ==========================================
    # Usiamo un custom command per tracciare le modifiche ai file
    add_custom_command(
        OUTPUT ${OUTPUT_MARKER}
        COMMAND echo "Generating beast-cpp c/cpp/h/hpp files from templates..."
        COMMAND ${FMPP_BIN}
        DEPENDS ${XML_MAIN_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/config.fmpp"
        COMMENT "Running FMPP template processor"
    )

    # Target manuale per FMPP
    add_custom_target(templates-build DEPENDS ${OUTPUT_MARKER})

    # Collegamento logico: la generazione richiede che la validazione passi per prima
    add_dependencies(templates-build registry-validate)
endif()

if(BEAST_BUILD_APPS)
    add_executable(beast-estimator apps/estimator/main.cpp)
    target_link_libraries(beast-estimator PRIVATE beast::beast)

    add_executable(beast-model-info apps/model-info/main.cpp)
    target_link_libraries(beast-model-info PRIVATE beast::beast)
endif()

if(BEAST_BUILD_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_executable(beast-catalog-test tests/test_catalog.cpp)
        target_link_libraries(beast-catalog-test PRIVATE beast::beast)
        add_test(NAME beast.catalog COMMAND beast-catalog-test)

        add_executable(beast-matrix-test tests/test_matrix.cpp)
        target_link_libraries(beast-matrix-test PRIVATE beast::beast)
        add_test(NAME beast.matrix COMMAND beast-matrix-test)

        add_executable(beast-debug-test tests/test_debug.cpp)
        target_link_libraries(beast-debug-test PRIVATE beast::beast)
        add_test(NAME beast.debug COMMAND beast-debug-test)

        add_executable(beast-modeldataloader-test tests/test_modeldataloader.cpp)
        target_link_libraries(beast-modeldataloader-test PRIVATE beast::beast)
        add_test(NAME beast.modeldataloader COMMAND beast-modeldataloader-test)
    endif()
endif()

if(BEAST_BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(BEAST_DOXYFILE_IN
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    )
    set(BEAST_DOXYFILE_OUT
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    )

    configure_file(
        ${BEAST_DOXYFILE_IN}
        ${BEAST_DOXYFILE_OUT}
        @ONLY
    )

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${BEAST_DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating BEAST API documentation with Doxygen"
        VERBATIM
    )
endif()

include(GNUInstallDirs)
install(TARGETS beast
    EXPORT beastTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT beastTargets
    FILE beastTargets.cmake
    NAMESPACE beast::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/beast-cpp
)
