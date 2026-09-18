#ifndef BEAST_RUNTIME_FACTORIES_H
#define BEAST_RUNTIME_FACTORIES_H

#include <memory>
#include <string>
#include <vector>

class CellModel;
class Estimator;

namespace beast {

std::unique_ptr<CellModel> make_cell_model(const std::string& name,
                                           const std::string& model_data_directory);
std::unique_ptr<Estimator> make_estimator(const std::string& name,
                                          CellModel* cell_model);

const std::vector<std::string>& supported_cell_models();
const std::vector<std::string>& supported_estimators();

} // namespace beast

#endif
