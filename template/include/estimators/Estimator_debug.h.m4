changequote(`$', `$')dnl
changecom()dnl
// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "$$BEAST_NAME$$" implementation.
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

#ifndef __ESTIMATOR_$$BEAST_UPNAME$$_DEBUG_H__
#define __ESTIMATOR_$$BEAST_UPNAME$$_DEBUG_H__

/* Debug Masks for Estimator "$$BEAST_UPNAME$$" */

#define DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_ENABLE        	0x80
#define DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_CLASS        	    0x01
#define DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_COERCE			0x02
#define DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_STEPBYSTEP		0x04


#define DEBUG_ESTIMATOR_$$BEAST_UPNAME$$       ( DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_ENABLE )

#define ESTIMATOR_$$BEAST_UPNAME$$_CHKDBG( dbg )      ( \
                            defined( DEBUG_ESTIMATOR_$$BEAST_UPNAME$$ ) && \
                            ( DEBUG_ESTIMATOR_$$BEAST_UPNAME$$ & DBGMSK_ESTIMATOR_$$BEAST_UPNAME$$_ENABLE ) && \ 
                            ( DEBUG_ESTIMATOR_$$BEAST_UPNAME$$ & (dbg) ) )

#if ESTIMATOR_$$BEAST_UPNAME$$_CHKDBG( DBGMSK_$$BEAST_UPNAME$$_ENABLE )
       #include <stdio.h>
       #include <stdlib.h>
       #define $$BEAST_CLASS_NAME$$_dprint( fmt ) do{ fprintf(fdbg, "$$BEAST_CLASS_NAME$$ :" fmt "\n"); fflush( fdbg ); } while(0)
#endif

#endif // __ESTIMATOR_$$BEAST_UPNAME$$_DEBUG_H__
