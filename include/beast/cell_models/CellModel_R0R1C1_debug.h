/* 
 * Class Debug File: CellModel_R0R1C1
 * Created by Salvatore Dello Iacono Mar 13-Mag-2014 16:36
 *
 */

#ifndef __CELLMODEL_R0R1C1_DEBUG_H__
#define __CELLMODEL_R0R1C1_DEBUG_H__



/* Tipi di debug disponibili */
#define DBG_R0R1C1_ENB          0x80
#define DBG_R0R1C1_CLASS        0x01

#define DBG_R0R1C1_FUNDBG       0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_R0R1C1_ENB oppure commentare la definizione.
 */
//#define DEBUG_R0R1C1       ( DBG_R0R1C1_ENB | DBG_R0R1C1_FUNDBG )

#define R0R1C1_DBG( dbg )      (defined(DEBUG_R0R1C1) && ( DEBUG_R0R1C1 & DBG_R0R1C1_ENB ) &&  ( DEBUG_R0R1C1 & (dbg) )  )


#if R0R1C1_DBG( DBG_R0R1C1_ENB )
       #include <stdio.h>
       #include <stdlib.h>
       #define R0R1C1_dprint( fmt ) do{ fprintf(fdbg, "R0R1C1 :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif // __CELLMODEL_R0R1C1_DEBUG_H__
