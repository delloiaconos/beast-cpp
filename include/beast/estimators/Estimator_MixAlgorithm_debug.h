// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "Mixed Algorithm" debug configuration file.
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


#ifndef __ESTIMATOR_MIXALGORITHM_DEBUG_H__
#define __ESTIMATOR_MIXALGORITHM_DEBUG_H__


/* Tipi di debug disponibili */
#define DBGMSK_MIXALGORITHM_ENABLE          	0x80
#define DBGMSK_MIXALGORITHM_CLASS        	0x01
#define DBGMSK_MIXALGORITHM_COERCE			0x02
#define DBGMSK_MIXALGORITHM_STEPBYSTEP		0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBGMSK_MIXALGORITHM_ENABLE oppure commentare la definizione.
 */
//#define DEBUG_MIXALGORITHM       ( DBGMSK_MIXALGORITHM_ENABLE | DBGMSK_MIXALGORITHM_OCV  )
#define DEBUG_MIXALGORITHM 0xFF

#ifndef DEBUG_MIXALGORITHM
#define DBGCHK_MIXALGORITHM( dbg )    (FALSE)
#else
#define DBGCHK_MIXALGORITHM( dbg ) ( \
     (DEBUG_MIXALGORITHM & DBGMSK_MIXALGORITHM_ENABLE) && \
     (DEBUG_MIXALGORITHM & (dbg)) )
#endif // DEBUG_MIXALGORITHM

#endif // __ESTIMATOR_MIXALGORITHM_DEBUG_H__
