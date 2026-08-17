/* 
 * Class Debug File: CellModel_R0R1C1R2C2
 * Created by Salvatore Dello Iacono Ven 12-Dic-2014 18:00
 *
 */

#ifndef __CELLMODEL_R0R1C1R2C2_DEBUG_H__
#define __CELLMODEL_R0R1C1R2C2_DEBUG_H__



/* Tipi di debug disponibili */
#define DBG_R0R1C1R2C2_ENB          0x80
#define DBG_R0R1C1R2C2_CLASS        0x01


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_R0R1C1R2C2_ENB oppure commentare la definizione.
 */
//#define DEBUG_R0R1C1R2C2       ( DBG_R0R1C1R2C2_ENB | DBG_R0R1C1R2C2_OCV )

#define R0R1C1R2C2_DBG( dbg )      (defined(DEBUG_R0R1C1R2C2) && ( DEBUG_R0R1C1R2C2 & DBG_R0R1C1R2C2_ENB ) &&  ( DEBUG_R0R1C1R2C2 & (dbg) )  )


#if R0R1C1R2C2_DBG( DBG_R0R1C1R2C2_ENB )
       #include stdio.h
       #include stdlib.h
       #define R0R1C1R2C2_dprint( fmt ) do{ fprintf(fdbg, "R0R1C1R2C2 :" fmt "\n"); fflush( fdbg ); } while(0)
#endif


#endif //__CELLMODEL_R0R1C1R2C2_DEBUG_H__
