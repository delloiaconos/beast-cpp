// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Interpolation functions header file.
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


#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__



#include <beast/common/architecture.h>



#ifdef __cplusplus
extern "C" {
#endif

t_float interp1( t_float * vect, t_uint n, t_float x );
t_float interpxy( t_float * vX, t_float * vY, t_uint n, t_float x );
#ifdef __cplusplus
}
#endif // extern "C"

#endif //__INTERPOLATION_H__
