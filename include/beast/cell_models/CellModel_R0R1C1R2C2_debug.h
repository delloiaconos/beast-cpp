// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model R0-R1C1-R2C2 debug configuration file. 
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

#ifndef __CELLMODEL_R0R1C1R2C2_DEBUG_H__
#define __CELLMODEL_R0R1C1R2C2_DEBUG_H__

/* Tipi di debug disponibili */
#define DBGMSK_R0R1C1R2C2_ENABLE   0x80
#define DBGMSK_R0R1C1R2C2_CLASS    0x01


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBGMSK_R0R1C1R2C2_ENABLE oppure commentare la definizione.
 */
//#define DEBUG_R0R1C1R2C2       ( DBGMSK_R0R1C1R2C2_ENABLE | DBGMSK_R0R1C1R2C2_OCV )

#define DBGCHK_R0R1C1R2C2( dbg )      (defined(DEBUG_R0R1C1R2C2) && ( DEBUG_R0R1C1R2C2 & DBGMSK_R0R1C1R2C2_ENABLE ) &&  ( DEBUG_R0R1C1R2C2 & (dbg) )  )


#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_ENABLE )
       #include stdio.h
       #include stdlib.h
       #define CellModel_R0R1C1R2C2_dprint( fmt ) do{ fprintf(fdbg, "CellModel_R0R1C1R2C2 :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif //__CELLMODEL_R0R1C1R2C2_DEBUG_H__
