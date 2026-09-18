// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model R0-A1B1 debug configuration file. 
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
 * https://github.com/delloiaconos/beast-cpp.git
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef __CELL_MODEL_R0A1B1_DEBUG_H__
#define __CELL_MODEL_R0A1B1_DEBUG_H__

/* Debug Masks for Cell Model "R0A1B1" */

#define DBGMSK_R0A1B1_ENABLE           0x80
#define DBGMSK_R0A1B1_CLASS            0x01
#define DBGMSK_R0A1B1_FUNCS            0x02
#define DBGMSK_R0A1B1_COERCE           0x04

#define DEBUG_R0A1B1       ( \
                            DBGMSK_R0A1B1_ENABLE | \
                            DBGMSK_R0A1B1_CLASS  | \
                            DBGMSK_R0A1B1_FUNCS )

#ifndef DEBUG_R0A1B1
#define DBGCHK_R0A1B1( dbg )    (FALSE)
#else
#define DBGCHK_R0A1B1( dbg )    ( \
                            ( DEBUG_R0A1B1 & DBGMSK_R0A1B1_ENABLE ) &&  \
                            ( DEBUG_R0A1B1 & (dbg) ) )
#endif // DEBUG_R0A1B1


#endif // __CELL_MODEL_R0A1B1_DEBUG_H__
