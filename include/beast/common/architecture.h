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
 * <REPOSITORY_URL>
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
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
