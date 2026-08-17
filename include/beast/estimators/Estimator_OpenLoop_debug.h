// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "Open Loop" debug configuration file.
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

#ifndef __ESTIMATOR_OPENLOOP_DEBUG_H__
#define __ESTIMATOR_OPENLOOP_DEBUG_H__


/* Tipi di debug disponibili */
#define DBG_OPENLOOP_ENB          	0x80
#define DBG_OPENLOOP_CLASS        	0x01
#define DBG_OPENLOOP_COERCE			0x02
#define DBG_OPENLOOP_STEPBYSTEP		0x04

#define DBG_OPENLOOP_OUT_LX			0x08
#define DBG_OPENLOOP_OUT_LP			0x10

/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_OPENLOOP_ENB oppure commentare la definizione.
 */
//#define DEBUG_OPENLOOP       ( DBG_OPENLOOP_ENB | DBG_OPENLOOP_OUT_LX | DBG_OPENLOOP_OUT_LP )

#define OPENLOOP_DBG( dbg )      (defined(DEBUG_OPENLOOP) && ( DEBUG_OPENLOOP & DBG_OPENLOOP_ENB ) &&  ( DEBUG_OPENLOOP & (dbg) )  )

#if OPENLOOP_DBG( DBG_OPENLOOP_ENB )
	#include <stdio.h>
	#include <stdlib.h>
	#define Estimator_OpenLoop_dprint( fmt ) do{ fprintf(fdbg, "Estimator_OpenLoop :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif // __ESTIMATOR_OPENLOOP_DEBUG_H__
