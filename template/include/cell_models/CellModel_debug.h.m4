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

#ifndef __CELL_MODEL_$$BEAST_UPPER_NAME$$_DEBUG_H__
#define __CELL_MODEL_$$BEAST_UPPER_NAME$$_DEBUG_H__

/* Debug Masks for Cell Model "$$BEAST_UPPER_NAME$$" */

#define DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_ENABLE       0x80
#define DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_CLASS        0x01
#define DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_FUNCS        0x02

#define DEBUG_CELL_MODEL_$$BEAST_UPPER_NAME$$       ( \
                            DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_ENABLE | \
                            DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_CLASS  | \
                            DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_FUNCS )

#define CELL_MODEL_$$BEAST_UPPER_NAME$$_CHKDBG( dbg )      ( \ 
                            defined(DEBUG_CELL_MODEL_$$BEAST_UPPER_NAME$$) && \
                            ( DEBUG_CELL_MODEL_$$BEAST_UPPER_NAME$$ & DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_ENABLE ) &&  \
                            ( DEBUG_CELL_MODEL_$$BEAST_UPPER_NAME$$ & (dbg) ) )

#if CELL_MODEL_$$BEAST_UPPER_NAME$$_CHKDBG( DBGMSK_CELL_MODEL_$$BEAST_UPPER_NAME$$_ENABLE )
       #include <stdio.h>
       #include <stdlib.h>
       #define $$BEAST_CLASS_NAME$$_dprint( fmt ) do{ fprintf(fdbg, "$$BEAST_CLASS_NAME$$ :" fmt "\n"); fflush( fdbg ); } while(0)
#endif

#endif // __CELL_MODEL_$$BEAST_UPPER_NAME$$_DEBUG_H__
