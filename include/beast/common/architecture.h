// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Architecture configuration file.
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


#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

/* Availables architectures */

#define ARCH_PC   				0x1
#define ARCH_NIOS 				0x2
#define ARCH_ARM 				0x4


/* Architecture masks */

#define ARCH_ATTR_SOFTFLOAT		0x01
#define ARCH_ATTR_FLOATS		0x02
#define ARCH_ATTR_DOUBLE		0x06
#define ARCH_ATTR_STREAMS		0x10
#define ARCH_ATTR_FILES			0x20


/* Define architecture HERE */
#define _ARCHITECTURE_ ARCH_PC

#ifndef _ARCHITECTURE_
#define ARCH_CHKTYPE( arch ) 		(FALSE)
#else
#define ARCH_CHKTYPE( arch )		( (arch) == _ARCHITECTURE_ )
#endif //_ARCHITECTURE_


#if ARCH_CHKTYPE( ARCH_NIOS )

	#define __FLOAT_T__
	typedef float t_float;

	#define __UINT_T__
	typedef unsigned int t_uint;

	#define __DIMS_T__
	typedef unsigned int t_size;
    //#pragma message( "single precision implementation" )

	#define _ARCHITECTURE_ATTR_ 	(ARCH_ATTR_SOFTFLOAT)

#elif ARCH_CHKTYPE( ARCH_PC )

	#define __FLOAT_T__
	typedef double t_float;

	#define __UINT_T__
	typedef unsigned int t_uint;

	#define __DIMS_T__
	typedef unsigned int t_size;
	//#pragma message( "double precision implementation" )
	
	#define _ARCHITECTURE_ATTR_ 	(ARCH_ATTR_DOUBLE | ARCH_ATTR_STREAMS | ARCH_ATTR_FILES)
#else

	#error _ARCHITECTURE_ not defined!
	
#endif //_ARCHITECTURE_


#ifndef _ARCHITECTURE_
#define ARCH_CHKATTR( attr ) 		(FALSE)
#else
#define ARCH_CHKATTR( attr )		( (attr) & _ARCHITECTURE_ATTR_ )
#endif //_ARCHITECTURE_

#endif // __ARCHITECTURE_H__
