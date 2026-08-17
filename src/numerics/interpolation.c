// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Interpolation Functions.
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

#include <beast/numerics/interpolation.h>

t_uint interp_round( t_float flt )
{
	return (t_uint) flt;
}

t_float interp1( t_float * vect, t_uint n, t_float x )
{
	t_uint ix;
	ix = interp_round( x );

	if( ix >= n )
		ix = n-1;

	return vect[ix];
}


t_float interpxy( t_float * vX, t_float * vY, t_uint n, t_float x )
{
	t_uint ix;

	ix = 0;

	do {
		if( vX[ix] < x ) {
			ix++;
		} else if( vX[ix] == x ) {
			return vY[ix];
		} else {
			if( ix > 0) {
				t_float dy = vY[ix] - vY[ix-1];
				t_float y0 = vY[ix-1];
				t_float dx = vX[ix] - vX[ix-1];
				t_float x0 = vX[ix-1];

				return ( dy/dx*( x - x0) + y0);
			} else {
				return vY[ix];
			}
		}
	} while( ix < n - 1);

	return vY[ix];
}

