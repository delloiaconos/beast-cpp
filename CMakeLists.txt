cmake_minimum_required(VERSION 3.16)

project(beast-cpp VERSION 0.2.0 LANGUAGES C CXX)

option(BEAST_BUILD_APPS "Build BEAST command-line utilities" ON)
option(BEAST_BUILD_TESTS "Build BEAST tests" ON)

add_library(beast
    src/common/Exception.cpp
    src/numerics/Matrix.cpp
    src/numerics/Matrix_functions.cpp
    src/numerics/gaussj.cpp
    src/numerics/interpolation.c
    src/cell_models/CellModel.cpp
    src/cell_models/CellModel_R0A1B1.cpp
    src/cell_models/CellModel_R0R1C1.cpp
    src/cell_models/CellModel_R0R1C1R2C2.cpp
    src/estimators/Estimator.cpp
    src/estimators/Estimator_EKFdual.cpp
    src/estimators/Estimator_EKFstate.cpp
    src/estimators/Estimator_MixAlgorithm.cpp
    src/estimators/Estimator_EnhancedMixAlgorithm.cpp
    src/estimators/Estimator_OpenLoop.cpp
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

if(BEAST_BUILD_APPS)
    add_executable(beast-estimator apps/estimator/main.cpp)
    target_link_libraries(beast-estimator PRIVATE beast::beast)

    add_executable(beast-model-info apps/model-info/main.cpp)
    target_link_libraries(beast-model-info PRIVATE beast::beast)
endif()

if(BEAST_BUILD_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_executable(beast-catalog-test tests/catalog_test.cpp)
        target_link_libraries(beast-catalog-test PRIVATE beast::beast)
        add_test(NAME beast.catalog COMMAND beast-catalog-test)

        add_executable(beast-matrix-test tests/matrix_test.cpp)
        target_link_libraries(beast-matrix-test PRIVATE beast::beast)
        add_test(NAME beast.matrix COMMAND beast-matrix-test)
    endif()
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
