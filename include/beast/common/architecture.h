/*
 * architecture.h
 *
 *  Created on: 31/mar/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__


#define ARCH_PC   1
#define ARCH_NIOS 2

/* Define architecture HERE */
#define _ARCHITECTURE_ ARCH_PC


#if _ARCHITECTURE_ == ARCH_NIOS

	#define __FLOAT_T__
	typedef float t_float;

	#define __UINT_T__
	typedef unsigned int t_uint;

	#define __DIMS_T__
	typedef unsigned int t_size;
    //#pragma message( "single precision implementation" )

#elif _ARCHITECTURE_ == ARCH_PC

	#define __FLOAT_T__
	typedef double t_float;

	#define __UINT_T__
	typedef unsigned int t_uint;

	#define __DIMS_T__
	typedef unsigned int t_size;
	//#pragma message( "double precision implementation" )

#else

	#error _ARCHITECTURE_ not defined!

#endif //_ARCHITECTURE_



#endif // __ARCHITECTURE_H__
