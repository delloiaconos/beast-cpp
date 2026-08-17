// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Application for displaying models information.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author Salvatore Dello Iacono
 * @date 2014
 *
 * @par Project
 * BEAST - Battery Estimation Architecture and Simulation Toolkit
 *
 * @par Repository
 * <REPOSITORY_URL>
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */


#include <beast/runtime/factories.h>

#include <iostream>

int main()
{
    std::cout << "Supported cell models:\n";
    for (const auto& name : beast::supported_cell_models()) {
        std::cout << " - " << name << '\n';
    }

    std::cout << "\nSupported estimators:\n";
    for (const auto& name : beast::supported_estimators()) {
        std::cout << " - " << name << '\n';
    }
    return 0;
}
