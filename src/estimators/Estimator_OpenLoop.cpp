// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator Implementation Open Loop.
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

#include <beast/estimators/Estimator_OpenLoop.h>
#include <beast/estimators/Estimator_OpenLoop_debug.h>

Estimator_OpenLoop::Estimator_OpenLoop()
{
	Nx = (t_size) 0;
	Np = (t_size) 0;

	Nu = (t_size) 0;
	Ny = (t_size) 0;

	told 		= (t_float) 0.0;

	xPold 		= Matrix( Nx, 1 );
	pPold 		= Matrix( Np, 1 );

}

Estimator_OpenLoop::Estimator_OpenLoop( CellModel * myCell )
{
	// Controllare se myCell e' non nulla
	Cell = myCell;

	Nx = Cell->Nx;
	Np = Cell->Np;

	Nu = Cell->Nu;
	Ny = Cell->Ny;

	// Inizialize X and P
	xPold 		= Matrix( Nx, 1 );
	pPold 		= Matrix( Np, 1 );

	told = (t_float) 0.0;
}

Estimator_OpenLoop::~Estimator_OpenLoop()
{};

t_float Estimator_OpenLoop::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
{

	pPold   = p0;
	xPold   = x0;

	told   = tnew;
	uold   = unew;


	return (t_float) 0.0;
}

t_float Estimator_OpenLoop::step( Vector &unew, Vector &yXPnew, t_float tnew )
{
	t_float deltat;
#if _ARCHITECTURE_ == ARCH_NIOS
	 deltat = tnew;
#else
	 deltat = tnew - told;
#endif

	 Vector xMnew = Matrix( Nx, 1 );
	 Cell->f0(xPold, pPold, unew, deltat, &xMnew );
	 Cell->CoerceState(&xMnew);

	 // Copy new State!
	 xPold = xMnew;

#if OPENLOOP_DBG( DBG_OPENLOOP_STEPBYSTEP )
    //printf( "sxPold\n");
    //sxPold.Print();
#endif

    return (t_float) 0;
}


t_size Estimator_OpenLoop::getX( Vector * const X)
{
	*X = xPold;
	return Nx;
}

t_size Estimator_OpenLoop::getP( Vector * const P)
{
	*P = pPold;
	return Np;
}


#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_OpenLoop::getLx( Vector * const Lx )
{
	return (t_size) 0;
}

#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_OpenLoop::getLp( Vector * const Lp )
{
	return (t_size) 0;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_OpenLoop::getSx( Vector * const Sx )
{
	return (t_size) 0;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_OpenLoop::getSp( Vector * const Sp )
{
	return (t_size) 0;
}
#endif

