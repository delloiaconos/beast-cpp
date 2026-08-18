#include <beast/io/ModelDataLoader.h>

#include <cassert>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

using beast::io::ModelDataLoader;


// -----------------------------------------------------------------------------
// Test utilities
// -----------------------------------------------------------------------------

static bool floatEqual(t_float a, t_float b)
{
    constexpr t_float eps = static_cast<t_float>(1e-12);

    return std::abs(a - b) < eps;
}


static void writeBinaryFile(
    const fs::path& path,
    const std::vector<t_float>& values)
{
    std::ofstream file(
        path,
        std::ios::binary | std::ios::trunc
    );

    assert(file.is_open());

    file.write(
        reinterpret_cast<const char*>(values.data()),
        static_cast<std::streamsize>(
            values.size() * sizeof(t_float)
        )
    );

    assert(file.good());
}


template<typename Func>
static void assertThrows(Func func)
{
    bool exceptionThrown = false;

    try {
        func();
    }
    catch (const std::exception&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
}


// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

static void test_constructor()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_constructor";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    ModelDataLoader loader(testDir);

    assert(loader.basePath() == testDir);

    fs::remove_all(testDir);
}


static void test_constructor_invalid_directory()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_missing";

    fs::remove_all(testDir);

    assertThrows([&]() {
        ModelDataLoader loader(testDir);
    });
}


static void test_read_scalar()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_scalar";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "scalar.bin",
        {static_cast<t_float>(42.5)}
    );

    ModelDataLoader loader(testDir);

    const t_float value =
        loader.readScalar("scalar.bin");

    assert(floatEqual(
        value,
        static_cast<t_float>(42.5)
    ));

    fs::remove_all(testDir);
}


static void test_read_vector()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_vector";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    const std::vector<t_float> expected = {
        static_cast<t_float>(1.0),
        static_cast<t_float>(2.0),
        static_cast<t_float>(3.5),
        static_cast<t_float>(-4.0)
    };

    writeBinaryFile(
        testDir / "vector.bin",
        expected
    );

    ModelDataLoader loader(testDir);

    const auto values =
        loader.readVector("vector.bin");

    assert(values.size() == expected.size());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        assert(floatEqual(
            values[i],
            expected[i]
        ));
    }

    fs::remove_all(testDir);
}


static void test_read_vector_expected_size()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_vector_size";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "vector.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0),
            static_cast<t_float>(3.0)
        }
    );

    ModelDataLoader loader(testDir);

    const auto values =
        loader.readVector("vector.bin", 3);

    assert(values.size() == 3);

    assert(floatEqual(values[0], 1.0));
    assert(floatEqual(values[1], 2.0));
    assert(floatEqual(values[2], 3.0));

    fs::remove_all(testDir);
}


static void test_read_vector_wrong_expected_size()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_wrong_size";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "vector.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0),
            static_cast<t_float>(3.0)
        }
    );

    ModelDataLoader loader(testDir);

    assertThrows([&]() {
        loader.readVector("vector.bin", 4);
    });

    fs::remove_all(testDir);
}


static void test_read_scalar_with_multiple_values()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_invalid_scalar";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "scalar.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0)
        }
    );

    ModelDataLoader loader(testDir);

    assertThrows([&]() {
        loader.readScalar("scalar.bin");
    });

    fs::remove_all(testDir);
}


static void test_missing_file()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_missing_file";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    ModelDataLoader loader(testDir);

    assertThrows([&]() {
        loader.readVector("does_not_exist.bin");
    });

    fs::remove_all(testDir);
}


static void test_invalid_file_size()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_invalid_file";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    const fs::path filePath =
        testDir / "invalid.bin";

    {
        std::ofstream file(
            filePath,
            std::ios::binary | std::ios::trunc
        );

        assert(file.is_open());

        // Intentionally write a byte count that is not a multiple
        // of sizeof(t_float).
        const char data[3] = {1, 2, 3};

        file.write(data, sizeof(data));
    }

    ModelDataLoader loader(testDir);

    assertThrows([&]() {
        loader.readVector("invalid.bin");
    });

    fs::remove_all(testDir);
}


static void test_read_diagonal()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_diagonal";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "diagonal.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0),
            static_cast<t_float>(3.0)
        }
    );

    ModelDataLoader loader(testDir);

    Matrix matrix(3, 3);

    loader.readDiagonal(
        "diagonal.bin",
        matrix
    );

    assert(floatEqual(matrix(1, 1), 1.0));
    assert(floatEqual(matrix(2, 2), 2.0));
    assert(floatEqual(matrix(3, 3), 3.0));

    // Off-diagonal elements should remain zero.
    assert(floatEqual(matrix(1, 2), 0.0));
    assert(floatEqual(matrix(1, 3), 0.0));

    assert(floatEqual(matrix(2, 1), 0.0));
    assert(floatEqual(matrix(2, 3), 0.0));

    assert(floatEqual(matrix(3, 1), 0.0));
    assert(floatEqual(matrix(3, 2), 0.0));

    fs::remove_all(testDir);
}


static void test_read_diagonal_wrong_size()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_diagonal_size";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "diagonal.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0)
        }
    );

    ModelDataLoader loader(testDir);

    Matrix matrix(3, 3);

    assertThrows([&]() {
        loader.readDiagonal(
            "diagonal.bin",
            matrix
        );
    });

    fs::remove_all(testDir);
}


static void test_read_diagonal_non_square_matrix()
{
    const fs::path testDir =
        fs::temp_directory_path() /
        "beast_test_model_data_loader_non_square";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    writeBinaryFile(
        testDir / "diagonal.bin",
        {
            static_cast<t_float>(1.0),
            static_cast<t_float>(2.0)
        }
    );

    ModelDataLoader loader(testDir);

    Matrix matrix(2, 3);

    assertThrows([&]() {
        loader.readDiagonal(
            "diagonal.bin",
            matrix
        );
    });

    fs::remove_all(testDir);
}


// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

int main()
{
    test_constructor();
    test_constructor_invalid_directory();

    test_read_scalar();
    test_read_scalar_with_multiple_values();

    test_read_vector();
    test_read_vector_expected_size();
    test_read_vector_wrong_expected_size();

    test_missing_file();
    test_invalid_file_size();

    test_read_diagonal();
    test_read_diagonal_wrong_size();
    test_read_diagonal_non_square_matrix();

    std::cout
        << "All ModelDataLoader tests passed."
        << std::endl;

    return 0;
}