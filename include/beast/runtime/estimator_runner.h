#ifndef BEAST_RUNTIME_ESTIMATOR_RUNNER_H
#define BEAST_RUNTIME_ESTIMATOR_RUNNER_H

#include <string>

namespace beast {

struct EstimatorRunConfig {
    std::string input_directory;
    std::string output_directory;
    std::string model_data_directory;
    std::string model_name;
    std::string estimator_name;
};

// Runs the legacy binary-data estimator workflow.
// Returns 0 on success and non-zero on configuration, I/O, or runtime failure.
int run_estimator(const EstimatorRunConfig& config);

} // namespace beast

#endif
