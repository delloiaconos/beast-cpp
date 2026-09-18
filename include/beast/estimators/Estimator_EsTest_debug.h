// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "EsTest" implementation.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author Salvatore Dello Iacono
 * @date 2026
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

#ifndef __ESTIMATOR_ESTEST_DEBUG_H__
#define __ESTIMATOR_ESTEST_DEBUG_H__

/* Debug Masks for Estimator "EsTest" */

#define DBGMSK_ESTEST_ENABLE           0x80
#define DBGMSK_ESTEST_CLASS            0x01
#define DBGMSK_ESTEST_COERCE           0x02
#define DBGMSK_ESTEST_STEPBYSTEP       0x04


#define DEBUG_ESTEST       ( \
                            DBGMSK_ESTEST_ENABLE | \
                            DBGMSK_ESTEST_CLASS )

#ifndef DEBUG_ESTEST
#define DBGCHK_ESTEST( dbg )    (FALSE)
#else
#define DBGCHK_ESTEST( dbg )    ( \
                            ( DEBUG_ESTEST & DBGMSK_ESTEST_ENABLE ) &&  \
                            ( DEBUG_ESTEST & (dbg) ) )
#endif // DEBUG_ESTEST

#endif // __ESTIMATOR_ESTEST_DEBUG_H__
