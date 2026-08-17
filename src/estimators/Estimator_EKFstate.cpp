// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator Implementation Enhanced Kalman Filter.
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

#include <beast/estimators/Estimator_EKFstate.h>
#include <beast/estimators/Estimator_EKFstate_debug.h>


Estimator_EKFstate::Estimator_EKFstate()
{
	Nx = (t_size) 0;
	Np = (t_size) 0;

	Nu = (t_size) 0;
	Ny = (t_size) 0;

	told 		= (t_float) 0.0;

	xPold 		= Matrix( Nx, 1 );
	pPold 		= Matrix( Np, 1 );

	sxPold 		= Matrix( Nx, Nx );

}

Estimator_EKFstate::Estimator_EKFstate( CellModel * myCell )
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

	sxPold 		= Matrix( Nx, Nx );

	told = (t_float) 0.0;
}

Estimator_EKFstate::~Estimator_EKFstate()
{}


t_float Estimator_EKFstate::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
{

	pPold   = p0;
	xPold   = x0;

	// dummy evolution for this step (fill the vector at initial position)
	sxPold  = Matrix( Matrix::Zeros, Nx, Nx );

	told   = tnew;
	uold   = unew;

	return (t_float) 0.0;
}


t_float Estimator_EKFstate::step( Vector &unew, Vector &yXPnew, t_float tnew )
{
	t_float deltat;
#if _ARCHITECTURE_ == ARCH_NIOS
	 deltat = tnew;
#else
	 deltat = tnew - told;
#endif

	// (1/6) state estimate time update
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 1/6 ==\n");
#endif
	Vector xMnew = Matrix( Nx, 1 );
	Cell->f0( xPold, pPold, uold, deltat, &xMnew );
	Cell->CoerceState( &xMnew );


	// (2/6) error covariance time update
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 2/6 ==\n");
#endif
	Matrix f1xold = Matrix( Nx, Nx );
	Matrix sxMnew = Matrix( Nx, Nx );

	Cell->f1x( xPold, pPold, uold, deltat, &f1xold );

	try{
		Matrix f1xoldT = Matrix( Nx, Nx );
	    sxMnew  = f1xold*sxPold*f1xoldT + Cell->sxW;
	} catch ( Exception& Ex ) { throw Ex; }

	// (3/6) Kalman gain computation
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 3/6 ==\n");
#endif
	Matrix g1xnew = Matrix( Ny, Nx );
	Matrix Lxnew = Matrix( Nx, Ny );

	Cell->g1x( xMnew, pPold, unew, deltat, &g1xnew );

	try {
		Matrix tmp1 = Matrix( Ny, Ny );
		//Matrix tmp2 = Matrix( Nx, Nx );
		Matrix tmp2I = Matrix( Nx, Nx );
		Matrix g1xnewT = Matrix( Ny, Nx );

		g1xnewT = g1xnew;
		g1xnewT.Transpose();

		tmp1  = g1xnew*sxMnew*g1xnewT;
		//tmp2  = tmp1 + Cell->sxV;
		tmp2I = Inv( tmp1 + Cell->sxV );

		Lxnew = sxMnew*g1xnewT*tmp2I; //Kalman gain matrix
	} catch( Exception& Ex ) { throw Ex; }

	// (4/6) state estimate measurement update
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 4/6 ==\n");
#endif

	Vector g0new = Matrix( Ny, 1 );
	Vector xPnew = Matrix( Nx, 1 );

	Cell->g0( xMnew, pPold, unew, deltat, &g0new );

	try {
		Vector xcorr = Matrix( Nx, 1 );
		xcorr = Lxnew*(yXPnew - g0new);
		xPnew = xMnew + xcorr;
		Cell->CoerceState( &xPnew );
	} catch( Exception& Ex ) { throw Ex; }

	// (5/6) error covariance measurement update
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 5/6 ==\n");
#endif
	Matrix sxPnew = Matrix( Nx, Nx );

	try {
		Matrix eyeNx = Matrix( Matrix::Identity, Nx, Nx );
		sxPnew = (eyeNx-Lxnew*g1xnew)*sxMnew;
	} catch( Exception& Ex ) { throw Ex; }

	// (6/6) preparing next step
#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_STEPBYSTEP )
	Estimator_EKFstate_dprint( "== 6/6 ==\n");
#endif

	told    = tnew;
	uold    = unew;
	xPold   = xPnew;
	sxPold  = sxPnew;

    return (t_float) 0;
}

t_size Estimator_EKFstate::getX( Vector * const X)
{
	*X = xPold;
	return Nx;
}

t_size Estimator_EKFstate::getP( Vector * const P)
{
	*P = pPold;
	return Np;
}

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EKFstate::getLx( Vector * const Lx )
{
	return Nx;
}
#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EKFstate::getLp( Vector * const Lp )
{
	return Np;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_EKFstate::getSx( Vector * const Sx )
{
	*Sx = sxPold;
	return Nx*Nx;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_EKFstate::getSp( Vector * const Sp )
{
	return (t_size) 0;
}
#endif
