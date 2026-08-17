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
 * https://github.com/delloiaconos/beast-cpp
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */
#ifndef __CELL_MODEL_R0R1C1_DEBUG_H__
#define __CELL_MODEL_R0R1C1_DEBUG_H__



/* Tipi di debug disponibili */
#define DBGMSK_R0A1B1_ENABLE          0x80
#define DBG_R0A1B1_CLASS        0x01
#define DBG_R0A1B1_COERCE		0x02


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBGMSK_R0A1B1_ENABLE oppure commentare la definizione.
 */
//#define DEBUG_R0A1B1       ( DBGMSK_R0A1B1_ENABLE | DBG_R0A1B1_OCV )

#define R0A1B1_DBG( dbg )      (defined(DEBUG_R0A1B1) && ( DEBUG_R0A1B1 & DBGMSK_R0A1B1_ENABLE ) &&  ( DEBUG_R0A1B1 & (dbg) )  )


#if R0A1B1_DBG( DBGMSK_R0A1B1_ENABLE )
       #include stdio.h
       #include stdlib.h
       #define CellModel_R0A1B1_dprint( fmt ) do{ fprintf(fdbg, "CellModel_R0A1B1 :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif // __CELLMODEL_R0R1C1_DEBUG_H__
