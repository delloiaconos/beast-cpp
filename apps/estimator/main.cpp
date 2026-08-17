#include <beast/runtime/estimator_runner.h>

#include <cstdio>
#include <string>

namespace {

void print_usage(const char* program)
{
    std::fprintf(stderr,
        "Usage: %s -i INPUT_DIR -o OUTPUT_DIR -m MODEL -e ESTIMATOR -d MODEL_DATA_DIR\n"
        "\n"
        "Example:\n"
        "  %s -i ./experiment -o ./out -m R0R1C1 -e EKFDUAL -d ./model\n",
        program, program);
}

bool next_value(int argc, char** argv, int& index, std::string& destination)
{
    if (index + 1 >= argc) {
        return false;
    }
    destination = argv[++index];
    return true;
}

} // namespace

int main(int argc, char** argv)
{
    beast::EstimatorRunConfig config;

    for (int i = 1; i < argc; ++i) {
        const std::string option = argv[i];
        if (option == "-h" || option == "--help") {
            print_usage(argv[0]);
            return 0;
        }
        if (option == "-i" && next_value(argc, argv, i, config.input_directory)) {
            continue;
        }
        if (option == "-o" && next_value(argc, argv, i, config.output_directory)) {
            continue;
        }
        if (option == "-m" && next_value(argc, argv, i, config.model_name)) {
            continue;
        }
        if (option == "-e" && next_value(argc, argv, i, config.estimator_name)) {
            continue;
        }
        if (option == "-d" && next_value(argc, argv, i, config.model_data_directory)) {
            continue;
        }

        std::fprintf(stderr, "Invalid or incomplete argument: %s\n", option.c_str());
        print_usage(argv[0]);
        return 2;
    }

    if (config.input_directory.empty() || config.output_directory.empty() ||
        config.model_name.empty() || config.estimator_name.empty() ||
        config.model_data_directory.empty()) {
        print_usage(argv[0]);
        return 2;
    }

    std::fprintf(stderr,
        "=========================================\n"
        "||             BEAST C++               ||\n"
        "||  Battery Estimation Algorithms      ||\n"
        "=========================================\n\n");

    return beast::run_estimator(config);
}
