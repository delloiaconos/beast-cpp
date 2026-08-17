#include <beast/runtime/factories.h>

#include <iostream>

int main()
{
    std::cout << "Supported cell models:\n";
    for (const auto& name : beast::supported_cell_models()) {
        std::cout << "  " << name << '\n';
    }

    std::cout << "\nSupported estimators:\n";
    for (const auto& name : beast::supported_estimators()) {
        std::cout << "  " << name << '\n';
    }
    return 0;
}
