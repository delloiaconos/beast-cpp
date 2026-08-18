#include <beast/runtime/factories.h>

#include <beast/cell_models/CellModel.h>
#include <beast/cell_models/CellModel_R0A1B1.h>
#include <beast/cell_models/CellModel_R0R1C1.h>
#include <beast/cell_models/CellModel_R0R1C1R2C2.h>

#include <stdexcept>

namespace beast {

const std::vector<std::string>& supported_cell_models()
{
    static const std::vector<std::string> names = {
        "R0A1B1",
        "R0R1C1",
        "R0R1C1R2C2"
    };
    return names;
}

std::unique_ptr<CellModel> make_cell_model(const std::string& name,
                                           const std::string& model_data_directory)
{
    // Legacy constructors accept char*. std::string::data() is writable in C++17.
    std::string path = model_data_directory;
    const char* basepath = path.empty() ? nullptr : path.data();

    if (name == "R0A1B1") {
        return std::make_unique<CellModel_R0A1B1>(basepath);
    }
    if (name == "R0R1C1") {
        return std::make_unique<CellModel_R0R1C1>(basepath);
    }
    if (name == "R0R1C1R2C2") {
        return std::make_unique<CellModel_R0R1C1R2C2>(basepath);
    }

    throw std::invalid_argument("Unknown cell model: " + name);
}

} // namespace beast
