// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Abstract Estimator Class.
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

#include <beast/estimators/Estimator.h>

Estimator::Estimator()
{
   Cell = (CellModel *) 0;

   Nx = 0;
   Np = 0;

   Ny = 0;
   Nu = 0;
}

Estimator::Estimator( CellModel * model )
{
   Cell = model;

   Nx = Cell->Nx;
   Np = Cell->Np;

   Nu = Cell->Nu;
   Ny = Cell->Ny;
}

Estimator::~Estimator()
{
   //Nothing
}


t_float Estimator::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
{
   (void) x0;
   (void) p0;
   (void) unew;
   (void) yXPnew;
	told = tnew;
	return (t_float) 0.0;
}

t_float Estimator::step( Vector &unew, Vector &yXPnew, t_float tnew )
{
   (void) unew;
   (void) yXPnew;
	told = tnew;
	return (t_float) 0.0;
}

t_size Estimator::getX( Vector * const X)
{
   (void) X;
	return Nx;
}

t_size Estimator::getP( Vector * const P)
{
   (void) P;
	return Np;
}


#ifdef ESTIMATOR_GET_GAINS
t_size Estimator::getLx( Vector * const Lx )
{
   (void) Lx;
	return Nx;
}
#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator::getLp( Vector * const Lp )
{
   (void) Lp;
	return Np;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator::getSx( Vector * const Sx )
{
   (void) Sx;
	return (t_size) 0;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator::getSp( Vector * const Sp )
{
   (void) Sp;
	return (t_size) 0;
}
#endif
