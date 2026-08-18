#ifndef __MODEL_DATA_LOADER_H__
#define __MODEL_DATA_LOADER_H__

#include <filesystem>
#include <string_view>
#include <vector>

#include <beast/common/architecture.h>
#include <beast/numerics/Matrix.h>

namespace beast::io
{

class ModelDataLoader
{
public:
    explicit ModelDataLoader(std::filesystem::path basePath);

    [[nodiscard]]
    t_float readScalar(std::string_view filename) const;

    [[nodiscard]]
    std::vector<t_float> readVector(std::string_view filename) const;

    [[nodiscard]]
    std::vector<t_float> readVector(
        std::string_view filename,
        t_size expectedCount
    ) const;

    void readDiagonal(
        std::string_view filename,
        Matrix& matrix
    ) const;

    [[nodiscard]]
    const std::filesystem::path& basePath() const noexcept
    {
        return basePath_;
    }

private:
    [[nodiscard]]
    std::filesystem::path makePath(std::string_view filename) const;

    [[nodiscard]]
    std::vector<t_float> readAll(
        std::string_view filename
    ) const;

private:
    std::filesystem::path basePath_;
};

}

#endif // __MODEL_DATA_LOADER_H__