#include <beast/runtime/estimator_runner.h>

#include <beast/common/Exception.h>
#include <beast/common/architecture.h>
#include <beast/estimators/Estimator.h>
#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>
#include <beast/runtime/factories.h>

#include <cstdio>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>

namespace beast {
namespace {

namespace fs = std::filesystem;

struct FileCloser {
    void operator()(FILE* file) const noexcept
    {
        if (file) {
            std::fclose(file);
        }
    }
};
using File = std::unique_ptr<FILE, FileCloser>;

File open_file(const fs::path& path, const char* mode)
{
    FILE* raw = std::fopen(path.string().c_str(), mode);
    if (!raw) {
        throw std::runtime_error("Unable to open file: " + path.string());
    }
    return File(raw);
}

void require_regular_file(const fs::path& path)
{
    if (!fs::is_regular_file(path)) {
        throw std::runtime_error("Required file not found: " + path.string());
    }
}

void validate_config(const EstimatorRunConfig& config)
{
    if (config.input_directory.empty() || config.output_directory.empty() ||
        config.model_data_directory.empty() || config.model_name.empty() ||
        config.estimator_name.empty()) {
        throw std::invalid_argument("All estimator configuration values are required");
    }

    const fs::path input(config.input_directory);
    const fs::path model(config.model_data_directory);
    require_regular_file(input / "MD_t_all.in");
    require_regular_file(input / "MD_u_all.in");
    require_regular_file(input / "MD_yXP_all.in");
    require_regular_file(model / "MD_x0.in");
    require_regular_file(model / "MD_p0.in");
    require_regular_file(model / "MD_COV_sxWvec.in");
    require_regular_file(model / "MD_COV_sxVvec.in");
    require_regular_file(model / "MD_COV_spRvec.in");
    require_regular_file(model / "MD_COV_spEvec.in");
    require_regular_file(model / "MD_pfix_Qn_Ah.in");
    require_regular_file(model / "MD_pfix_eta.in");
    require_regular_file(model / "MD_pfix_soc.in");
    require_regular_file(model / "MD_pfix_ocv0.in");
    require_regular_file(model / "MD_pfix_ocv1.in");

    fs::create_directories(fs::path(config.output_directory));
}

bool read_sample(FILE* time_file, FILE* input_file, FILE* measure_file,
                 t_float& time, Vector& input, Vector& measures)
{
    if (std::fread(&time, sizeof(t_float), 1, time_file) != 1) {
        return false;
    }

    const t_size input_count = input.GetRows() * input.GetCols();
    const t_size measure_count = measures.GetRows() * measures.GetCols();
    if (input.mread(input_file) != input_count) {
        throw std::runtime_error("Input stream ended mid-sample");
    }
    if (measures.mread(measure_file) != measure_count) {
        throw std::runtime_error("Measurement stream ended mid-sample");
    }
    return true;
}

void write_estimator_output(Estimator& estimator, FILE* state_file, FILE* parameter_file,
#ifdef ESTIMATOR_GET_GAINS
                            FILE* state_gain_file, FILE* parameter_gain_file,
#endif
                            Vector& state, Vector& parameters
#ifdef ESTIMATOR_GET_GAINS
                            , Matrix& state_gain, Matrix& parameter_gain
#endif
                            )
{
    estimator.getX(&state);
    state.mwrite(state_file);

    estimator.getP(&parameters);
    parameters.mwrite(parameter_file);

#ifdef ESTIMATOR_GET_GAINS
    estimator.getLx(&state_gain);
    state_gain.mwrite(state_gain_file);
    estimator.getLp(&parameter_gain);
    parameter_gain.mwrite(parameter_gain_file);
#endif
}

} // namespace

int run_estimator(const EstimatorRunConfig& config)
{
    try {
        validate_config(config);

        const fs::path input_dir(config.input_directory);
        const fs::path output_dir(config.output_directory);
        const fs::path model_dir(config.model_data_directory);

        auto time_file = open_file(input_dir / "MD_t_all.in", "rb");
        auto input_file = open_file(input_dir / "MD_u_all.in", "rb");
        auto measure_file = open_file(input_dir / "MD_yXP_all.in", "rb");
        auto state0_file = open_file(model_dir / "MD_x0.in", "rb");
        auto parameter0_file = open_file(model_dir / "MD_p0.in", "rb");

        auto state_out = open_file(output_dir / "xP_all.out", "wb");
        auto parameter_out = open_file(output_dir / "pP_all.out", "wb");
#ifdef ESTIMATOR_GET_GAINS
        auto state_gain_out = open_file(output_dir / "Lx_all.out", "wb");
        auto parameter_gain_out = open_file(output_dir / "Lp_all.out", "wb");
#endif

        auto cell = make_cell_model(config.model_name, config.model_data_directory);
        auto estimator = make_estimator(config.estimator_name, cell.get());

        std::fprintf(stderr, "CELLMODEL: %s\n", config.model_name.c_str());
        std::fprintf(stderr, "ESTIMATOR: %s\n", config.estimator_name.c_str());

        t_float time = static_cast<t_float>(0.0);
        Vector input = Matrix(cell->Nu, 1);
        Vector measures = Matrix(cell->Ny, 1);
        Vector state = Matrix(cell->Nx, 1);
        Vector parameters = Matrix(cell->Np, 1);
#ifdef ESTIMATOR_GET_GAINS
        Matrix state_gain(cell->Nx, cell->Ny);
        Matrix parameter_gain(cell->Np, cell->Ny);
#endif

        if (!read_sample(time_file.get(), input_file.get(), measure_file.get(), time, input, measures)) {
            throw std::runtime_error("Input dataset is empty");
        }
        if (state.mread(state0_file.get()) != state.GetRows() * state.GetCols()) {
            throw std::runtime_error("Invalid MD_x0.in size");
        }
        if (parameters.mread(parameter0_file.get()) != parameters.GetRows() * parameters.GetCols()) {
            throw std::runtime_error("Invalid MD_p0.in size");
        }

        estimator->initialize(state, parameters, input, measures, time);
        write_estimator_output(*estimator, state_out.get(), parameter_out.get(),
#ifdef ESTIMATOR_GET_GAINS
                               state_gain_out.get(), parameter_gain_out.get(),
#endif
                               state, parameters
#ifdef ESTIMATOR_GET_GAINS
                               , state_gain, parameter_gain
#endif
                               );

        unsigned long count = 1;
        while (read_sample(time_file.get(), input_file.get(), measure_file.get(), time, input, measures)) {
            estimator->step(input, measures, time);
            ++count;
            write_estimator_output(*estimator, state_out.get(), parameter_out.get(),
#ifdef ESTIMATOR_GET_GAINS
                                   state_gain_out.get(), parameter_gain_out.get(),
#endif
                                   state, parameters
#ifdef ESTIMATOR_GET_GAINS
                                   , state_gain, parameter_gain
#endif
                                   );
            if ((count % 10) == 0) {
                std::fprintf(stderr, "cnt = %lu; t = %f\n", count, static_cast<double>(time));
            }
        }

        std::fprintf(stderr, "Estimator completed: %lu samples\n", count);
        return 0;
    } catch (const Exception& ex) {
        std::fprintf(stderr, "BEAST exception: %s\n", ex.what());
    } catch (const std::exception& ex) {
        std::fprintf(stderr, "Error: %s\n", ex.what());
    }
    return 1;
}

} // namespace beast
