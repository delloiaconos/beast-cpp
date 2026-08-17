// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief GaussJordan header file.
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


#ifndef __GAUSSJ_H__
#define __GAUSSJ_H__

#include <beast/common/commons.h>
#include <beast/numerics/Matrix.h>

#define GAUSSJ_MATRIXCHECK TRUE

t_size gaussj_AxB( Matrix& aa, Matrix& bb );
t_size gaussj_xAB( Matrix& aa, Matrix& bb );

#endif // __GAUSSJ_H__
