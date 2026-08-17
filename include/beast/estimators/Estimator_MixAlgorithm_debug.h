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
 * <REPOSITORY_URL>
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
#define DBG_MIXALGORITHM_ENB          	0x80
#define DBG_MIXALGORITHM_CLASS        	0x01
#define DBG_MIXALGORITHM_COERCE			0x02
#define DBG_MIXALGORITHM_STEPBYSTEP		0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_MIXALGORITHM_ENB oppure commentare la definizione.
 */
//#define DEBUG_MIXALGORITHM       ( DBG_MIXALGORITHM_ENB | DBG_MIXALGORITHM_OCV )

#define MIXALGORITHM_DBG( dbg )      (defined(DEBUG_MIXALGORITHM) && ( DEBUG_MIXALGORITHM & DBG_MIXALGORITHM_ENB ) &&  ( DEBUG_MIXALGORITHM & (dbg) )  )


#if MIXALGORITHM_DBG( DBG_MIXALGORITHM_ENB )

#endif


#endif // __ESTIMATOR_MIXALGORITHM_DEBUG_H__
