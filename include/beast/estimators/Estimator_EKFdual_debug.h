/*
 * Estimator_EKFdual_debug.h
 *
 *  Created on: 18/giu/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ESTIMATOR_EKFDUAL_DEBUG_H__
#define __ESTIMATOR_EKFDUAL_DEBUG_H__


/* Tipi di debug disponibili */
#define DBG_EKFDUAL_ENB          	0x80
#define DBG_EKFDUAL_CLASS        	0x01
#define DBG_EKFDUAL_COERCE			0x02
#define DBG_EKFDUAL_STEPBYSTEP		0x04

#define DBG_EKFDUAL_OUT_LX			0x08
#define DBG_EKFDUAL_OUT_LP			0x10

/* Imposta debug
 * bisogna mettere in "or" le costanti definite sopra per
 * abilitare i vari tipi di debug testuale.
 * Per disabilitare togliere DBG_EKFDUAL_ENB oppure commentare la definizione.
 */
//#define DEBUG_EKFDUAL       ( DBG_EKFDUAL_ENB | DBG_EKFDUAL_OUT_LX | DBG_EKFDUAL_OUT_LP )

#define EKFDUAL_DBG( dbg )      (defined(DEBUG_EKFDUAL) && ( DEBUG_EKFDUAL & DBG_EKFDUAL_ENB ) &&  ( DEBUG_EKFDUAL & (dbg) )  )

#if EKFDUAL_DBG( DBG_EKFDUAL_ENB )
	#include <stdio.h>
	#include <stdlib.h>
#endif


#endif // __ESTIMATOR_EKFDUAL_DEBUG_H__
