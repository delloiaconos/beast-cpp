/* 
 * Class Debug File: CellModel_R0A1B1_debug
 * Created by Salvatore Dello Iacono Gio 17-Apr-2014 10:34
 *
 */

#ifndef __CELL_MODEL_R0R1C1_DEBUG_H__
#define __CELL_MODEL_R0R1C1_DEBUG_H__



/* Tipi di debug disponibili */
#define DBG_R0A1B1_ENB          0x80
#define DBG_R0A1B1_CLASS        0x01
#define DBG_R0A1B1_COERCE		0x02


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_R0A1B1_ENB oppure commentare la definizione.
 */
//#define DEBUG_R0A1B1       ( DBG_R0A1B1_ENB | DBG_R0A1B1_OCV )

#define R0A1B1_DBG( dbg )      (defined(DEBUG_R0A1B1) && ( DEBUG_R0A1B1 & DBG_R0A1B1_ENB ) &&  ( DEBUG_R0A1B1 & (dbg) )  )


#if R0A1B1_DBG( DBG_R0A1B1_ENB )
       #include stdio.h
       #include stdlib.h
       #define dbg_print( fmt ) do{ fprintf(fdbg, "CellModel_R0A1B1" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif // __CELLMODEL_R0R1C1_DEBUG_H__
