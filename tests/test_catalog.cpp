#include <beast/runtime/factories.h>
#include <algorithm>
#include <cassert>
#include <string>

int main()
{
    const auto& models = beast::supported_cell_models();
    const auto& estimators = beast::supported_estimators();
    assert(std::find(models.begin(), models.end(), std::string("R0R1C1")) != models.end());
    assert(std::find(estimators.begin(), estimators.end(), std::string("EKFDUAL")) != estimators.end());
    assert(std::find(estimators.begin(), estimators.end(), std::string("OPENLOOP")) != estimators.end());
    return 0;
}
