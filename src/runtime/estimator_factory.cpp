#include <beast/runtime/factories.h>

#include <beast/cell_models/CellModel.h>
#include <beast/estimators/Estimator.h>
#include <beast/estimators/Estimator_EKFdual.h>
#include <beast/estimators/Estimator_EKFstate.h>
#include <beast/estimators/Estimator_EnhancedMixAlgorithm.h>
#include <beast/estimators/Estimator_MixAlgorithm.h>
#include <beast/estimators/Estimator_OpenLoop.h>

#include <stdexcept>

namespace beast {

const std::vector<std::string>& supported_estimators()
{
    static const std::vector<std::string> names = {
        "EKFDUAL",
        "EKFSTATE",
        "MIXALGORITHM",
        "ENHANCEDMIXALGORITHM",
        "OPENLOOP"
    };
    return names;
}

std::unique_ptr<Estimator> make_estimator(const std::string& name,
                                          CellModel* cell_model)
{
    if (!cell_model) {
        throw std::invalid_argument("Cell model must not be null");
    }
    if (name == "EKFDUAL") {
        return std::make_unique<Estimator_EKFdual>(cell_model);
    }
    if (name == "EKFSTATE") {
        return std::make_unique<Estimator_EKFstate>(cell_model);
    }
    if (name == "MIXALGORITHM") {
        return std::make_unique<Estimator_MixAlgorithm>(cell_model);
    }
    if (name == "ENHANCEDMIXALGORITHM") {
        return std::make_unique<Estimator_EnhancedMixAlgorithm>(cell_model);
    }
    if (name == "OPENLOOP") {
        return std::make_unique<Estimator_OpenLoop>(cell_model);
    }

    throw std::invalid_argument("Unknown estimator: " + name);
}

} // namespace beast
