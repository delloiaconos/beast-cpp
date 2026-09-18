// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Exeception Class header file. 
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
 * https://github.com/delloiaconos/beast-cpp
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef BEAST_EXCEPTION_H
#define BEAST_EXCEPTION_H

#include <stdexcept>

class Exception : public std::runtime_error
{
public:
    explicit Exception(const char* arg);
    const char* msg;
};

#endif
