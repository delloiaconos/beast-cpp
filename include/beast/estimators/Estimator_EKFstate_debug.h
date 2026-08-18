// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "Kalman Filter" debug configuration file.
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


#ifndef __ESTIMATOR_EKFSTATE_DEBUG_H__
#define __ESTIMATOR_EKFSTATE_DEBUG_H__


/* Tipi di debug disponibili */
#define DBGMSK_EKFSTATE_ENABLE          	0x80
#define DBGMSK_EKFSTATE_CLASS        	0x01
#define DBGMSK_EKFSTATE_COERCE			0x02
#define DBGMSK_EKFSTATE_STEPBYSTEP		0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBGMSK_EKFSTATE_ENABLE oppure commentare la definizione.
 */
//#define DEBUG_EKFSTATE       ( DBGMSK_EKFSTATE_ENABLE | DBGMSK_EKFSTATE_OCV )
#define DEBUG_EKFSTATE  0xFF

#ifndef DEBUG_EKFSTATE
#define DBGCHK_EKFSTATE( dbg )    (FALSE)
#else
#define DBGCHK_EKFSTATE( dbg ) ( \
     (DEBUG_EKFSTATE & DBGMSK_EKFSTATE_ENABLE) && \
     (DEBUG_EKFSTATE & (dbg)) )
#endif // DEBUG_EKFSTATE


#endif // __ESTIMATOR_EKFSTATE_DEBUG_H__
