// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Abstract CellModel debug configuration file. 
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
#ifndef __CELL_MODEL_DEBUG_H__
#define __CELL_MODEL_DEBUG_H__

#define DBGMSK_CELL_MODEL_INFO  0x01

#define DEBUG_CELL_MODEL        ( DBGMSK_CELL_MODEL_INFO )


#define DBGCHK_CELL_MODEL( dbg )      ( \
                defined( DEBUG_CELL_MODEL ) && \
                ( DEBUG_CELL_MODEL & DBGMSK_CELL_MODEL_ENABLE ) && \
                ( DEBUG_CELL_MODEL & (dbg) ) )

#endif // __CELL_MODEL_DEBUG_H__
