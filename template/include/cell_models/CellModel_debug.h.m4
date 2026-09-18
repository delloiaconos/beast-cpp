changequote(`$', `$')dnl
changecom()dnl
// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "$$BEAST_NAME$$" debug header file.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author $$BEAST_AUTHOR$$
 * @date $$BEAST_YEAR$$
 *
 * @par Project
 * BEAST - Battery Estimation Architecture and Simulation Toolkit
 *
 * @par Repository
 * $$BEAST_REPOSITORY$$
 *
 * @copyright
 * Copyright (c) $$BEAST_YEAR$$ $$BEAST_AUTHOR$$.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef __CELL_MODEL_$$BEAST_UPNAME$$_DEBUG_H__
#define __CELL_MODEL_$$BEAST_UPNAME$$_DEBUG_H__

/* Debug Masks for Cell Model "$$BEAST_NAME$$" */

#define DBGMSK_$$BEAST_UPNAME$$_ENABLE           0x80
#define DBGMSK_$$BEAST_UPNAME$$_CLASS            0x01
#define DBGMSK_$$BEAST_UPNAME$$_FUNCS            0x02
#define DBGMSK_$$BEAST_UPNAME$$_COERCE           0x04

#define DEBUG_$$BEAST_UPNAME$$       ( \
                            DBGMSK_$$BEAST_UPNAME$$_ENABLE | \
                            DBGMSK_$$BEAST_UPNAME$$_CLASS  | \
                            DBGMSK_$$BEAST_UPNAME$$_FUNCS )

#ifndef DEBUG_$$BEAST_UPNAME$$
#define DBGCHK_$$BEAST_UPNAME$$( dbg )    (FALSE)
#else
#define DBGCHK_$$BEAST_UPNAME$$( dbg )    ( \
                            ( DEBUG_$$BEAST_UPNAME$$ & DBGMSK_$$BEAST_UPNAME$$_ENABLE ) &&  \
                            ( DEBUG_$$BEAST_UPNAME$$ & (dbg) ) )
#endif // DEBUG_$$BEAST_UPNAME$$


#endif // __CELL_MODEL_$$BEAST_UPNAME$$_DEBUG_H__
