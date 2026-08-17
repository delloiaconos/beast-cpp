// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator Implementation Enhanced Mixed Algorithm.
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

#include <beast/estimators/Estimator_EnhancedMixAlgorithm.h>
#include <beast/estimators/Estimator_EnhancedMixAlgorithm_debug.h>


Estimator_EnhancedMixAlgorithm::Estimator_EnhancedMixAlgorithm()
{
	Nx = (t_size) 0;
	Np = (t_size) 0;

	Nu = (t_size) 0;
	Ny = (t_size) 0;

	told = (t_float) 0.0;

}

Estimator_EnhancedMixAlgorithm::Estimator_EnhancedMixAlgorithm( CellModel * myCell )
{
	// Controllare se myCell e' non nulla
	Cell = myCell;

	Nx = Cell->Nx;
	Np = Cell->Np;

	Nu = Cell->Nu;
	Ny = Cell->Ny;

	// Inizialize X and P

	told = (t_float) 0.0;
}

Estimator_EnhancedMixAlgorithm::~Estimator_EnhancedMixAlgorithm()
{}


t_float Estimator_EnhancedMixAlgorithm::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
{

	pPold   = p0;
	xPold   = x0;

	// dummy evolution for this step (fill the vector at initial position)
	//sxPold  = Matrix( Matrix::Zeros, Nx, Nx );
	Lxold = Matrix( Nx, Ny );
	/* ATTENZIONE
	 * non Nx X Nx ma Nx x Ny
	 * Per ora funziona... ma e' sbagliato
	 * */
	for( t_size kk = 1; kk <= Cell->Nx; kk++ )
			Lxold( kk, kk ) = 1E5 * Cell->sxW( kk, kk );

	/* TODO
	 * Assegnare LP */
	Lpold = Matrix( Np, Ny );

	told    = tnew;

	return (t_float) 0.0;
}


t_float Estimator_EnhancedMixAlgorithm::step( Vector &unew, Vector &yXPnew, t_float tnew )
{
	t_float deltat;
#if _ARCHITECTURE_ == ARCH_NIOS
	 deltat = tnew;
#else
	 deltat = tnew - told;
#endif

	// (1/6) state estimate time update

	Vector xMnew = Matrix( Nx, 1 );
	Cell->f0(xPold, pPold, unew, deltat, &xMnew );
	Cell->CoerceState(&xMnew);

	Vector g0new = Matrix( Ny, 1 );
	Vector xPnew = Matrix( Nx, 1 );
	Vector pPnew = Matrix( Np, 1 );

	Matrix Lpnew = Matrix( Np, Ny );

	Cell->g0( xMnew, pPold, unew, deltat, &g0new );

	try {
			Vector err 		= Matrix( Ny, 1 );
			Vector xcorr 	= Matrix( Nx, 1 );
			Vector pcorr 	= Matrix( Np, 1 );

			/* TODO Aggiustare Guadagno Lp...*/
			Lpnew = ( unew(1,1) >= 0 ? 1 : -1 )*Lpold;

			err = yXPnew - g0new;

			xcorr = 1e5*Lxold*err;
		    xPnew = xMnew + xcorr;

		    pcorr = Lpnew*err;
		    pPnew = pPold + pcorr;

	} catch( Exception& Ex ) { throw Ex; }

	Cell->CoerceState( &xPnew );
	Cell->CoercePars( &pPnew );


    told  = tnew;

    xPold = xPnew;
    pPold = pPnew;
    Lpold = Lpnew;
    return (t_float) 0;
}


t_size Estimator_EnhancedMixAlgorithm::getX( Vector * const X)
{
	*X = xPold;
	return Nx;
}

t_size Estimator_EnhancedMixAlgorithm::getP( Vector * const P)
{
	*P = pPold;
	return Np;
}

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EnhancedMixAlgorithm::getLx( Vector * const Lx )
{
	*Lx = Lxold;
	return Nx;
}
#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EnhancedMixAlgorithm::getLp( Vector * const Lp )
{
	*Lp = Lpold;
	return Np;
}
#endif


#ifdef ESTIMATOR_GET_COV
t_size Estimator_EnhancedMixAlgorithm::getSx( Vector * const Sx )
{
	return (t_size) 0;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_EnhancedMixAlgorithm::getSp( Vector * const Sp )
{
	return (t_size) 0;
}
#endif
