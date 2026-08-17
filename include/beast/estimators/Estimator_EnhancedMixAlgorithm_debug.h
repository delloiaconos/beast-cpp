/*
 * Estimator_EnhancedMixAlgorithm_debug.h
 *
 *  Created on: 18/giu/2014
 *      Author: salvatoredelloiacono
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

#endif


#endif // __ESTIMATOR_ENHANCEDMIXALGORITHM_DEBUG_H__
