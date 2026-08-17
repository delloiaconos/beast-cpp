/*
 * Estimator_MIXALGORITHM_debug.h
 *
 *  Created on: 18/giu/2014
 *      Author: salvatoredelloiacono
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
