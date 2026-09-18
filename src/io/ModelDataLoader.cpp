#include <beast/io/ModelDataLoader.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace beast::io
{

ModelDataLoader::ModelDataLoader(std::filesystem::path basePath)
    : basePath_(std::move(basePath))
{
    if (basePath_.empty()) {
        throw std::invalid_argument(
            "ModelDataLoader: base path is empty"
        );
    }

    if (!std::filesystem::exists(basePath_)) {
        throw std::runtime_error(
            "ModelDataLoader: directory does not exist: " +
            basePath_.string()
        );
    }

    if (!std::filesystem::is_directory(basePath_)) {
        throw std::runtime_error(
            "ModelDataLoader: path is not a directory: " +
            basePath_.string()
        );
    }
}


std::filesystem::path ModelDataLoader::makePath(
    std::string_view filename
) const
{
    return basePath_ / std::filesystem::path(filename);
}


std::vector<t_float> ModelDataLoader::readAll(
    std::string_view filename
) const
{
    const auto path = makePath(filename);

    std::ifstream file(
        path,
        std::ios::binary | std::ios::ate
    );

    if (!file) {
        throw std::runtime_error(
            "Cannot open model data file: " +
            path.string()
        );
    }

    const std::streamsize byteCount = file.tellg();

    if (byteCount < 0) {
        throw std::runtime_error(
            "Cannot determine file size: " +
            path.string()
        );
    }

    if (byteCount % sizeof(t_float) != 0) {
        throw std::runtime_error(
            "Invalid model data file size: " +
            path.string()
        );
    }

    const std::size_t elementCount =
        static_cast<std::size_t>(byteCount) /
        sizeof(t_float);

    std::vector<t_float> values(elementCount);

    file.seekg(0, std::ios::beg);

    if (elementCount > 0) {
        file.read(
            reinterpret_cast<char*>(values.data()),
            byteCount
        );

        if (!file) {
            throw std::runtime_error(
                "Error reading model data file: " +
                path.string()
            );
        }
    }

    return values;
}


t_float ModelDataLoader::readScalar(
    std::string_view filename
) const
{
    const auto values = readVector(filename, 1);

    return values[0];
}


std::vector<t_float> ModelDataLoader::readVector(
    std::string_view filename
) const
{
    return readAll(filename);
}


std::vector<t_float> ModelDataLoader::readVector(
    std::string_view filename,
    t_size expectedCount
) const
{
    auto values = readAll(filename);

    if (values.size() != expectedCount) {
        std::ostringstream message;

        message
            << "Invalid number of values in "
            << makePath(filename)
            << ": expected "
            << expectedCount
            << ", found "
            << values.size();

        throw std::runtime_error(message.str());
    }

    return values;
}


void ModelDataLoader::readDiagonal(
    std::string_view filename,
    Matrix& matrix
) const
{
    if (matrix.GetRows() != matrix.GetCols()) {
        throw std::invalid_argument(
            "readDiagonal requires a square matrix"
        );
    }

    const auto values =
        readVector(filename, matrix.GetRows());

    for (t_size i = 0; i < matrix.GetRows(); ++i) {
        matrix(i + 1, i + 1) = values[i];
    }
}

}