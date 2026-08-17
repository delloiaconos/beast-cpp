// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "Enhanced Mixed Algorithm" debug configuration file.
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

#ifndef __ESTIMATOR_ENHANCEDMIXALGORITHM_DEBUG_H__
#define __ESTIMATOR_ENHANCEDMIXALGORITHM_DEBUG_H__


/* Tipi di debug disponibili */
#define DBG_ENHANCEDMIXALGORITHM_ENB          	0x80
#define DBG_ENHANCEDMIXALGORITHM_CLASS        	0x01
#define DBG_ENHANCEDMIXALGORITHM_COERCE			0x02
#define DBG_ENHANCEDMIXALGORITHM_STEPBYSTEP		0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_ENHANCEDMIXALGORITHM_ENB oppure commentare la definizione.
 */
//#define DEBUG_MIXALGORITHM       ( DBG_ENHANCEDMIXALGORITHM_ENB | DBG_ENHANCEDMIXALGORITHM_OCV )

#define ENHANCEDMIXALGORITHM_DBG( dbg )      (defined(DEBUG_MIXALGORITHM) && ( DEBUG_MIXALGORITHM & DBG_ENHANCEDMIXALGORITHM_ENB ) &&  ( DEBUG_MIXALGORITHM & (dbg) )  )


#if ENHANCEDMIXALGORITHM_DBG( DBG_ENHANCEDMIXALGORITHM_ENB )
	#include <stdio.h>
	#include <stdlib.h>
	#define Estimator_EnhancedMixAlgorithm_dprint( fmt ) do{ fprintf(fdbg, "Estimator_EnhancedMixAlgorithm :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif // __ESTIMATOR_ENHANCEDMIXALGORITHM_DEBUG_H__
