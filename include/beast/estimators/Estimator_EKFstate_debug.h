/*
 * Estimator_EKFSTATE_debug.h
 *
 *  Created on: 18/giu/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ESTIMATOR_EKFSTATE_DEBUG_H__
#define __ESTIMATOR_EKFSTATE_DEBUG_H__


/* Tipi di debug disponibili */
#define DBG_EKFSTATE_ENB          	0x80
#define DBG_EKFSTATE_CLASS        	0x01
#define DBG_EKFSTATE_COERCE			0x02
#define DBG_EKFSTATE_STEPBYSTEP		0x04


/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_EKFSTATE_ENB oppure commentare la definizione.
 */
//#define DEBUG_EKFSTATE       ( DBG_EKFSTATE_ENB | DBG_EKFSTATE_OCV )

#define EKFSTATE_DBG( dbg )      (defined(DEBUG_EKFSTATE) && ( DEBUG_EKFSTATE & DBG_EKFSTATE_ENB ) &&  ( DEBUG_EKFSTATE & (dbg) )  )


#if EKFSTATE_DBG( DBG_EKFSTATE_ENB )

#endif


#endif // __ESTIMATOR_EKFSTATE_DEBUG_H__
