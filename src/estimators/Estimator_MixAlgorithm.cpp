/*
 * Estimator_MixAlgorithm.cpp
 *
 *  Created on: 04/mag/2014
 *      Author: salvatoredelloiacono
 */


#include <beast/estimators/Estimator_MixAlgorithm.h>
#include <beast/estimators/Estimator_MixAlgorithm_debug.h>


Estimator_MixAlgorithm::Estimator_MixAlgorithm()
{
	Nx = (t_size) 0;
	Np = (t_size) 0;

	Nu = (t_size) 0;
	Ny = (t_size) 0;

	told = (t_float) 0.0;

}

Estimator_MixAlgorithm::Estimator_MixAlgorithm( CellModel * myCell )
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

Estimator_MixAlgorithm::~Estimator_MixAlgorithm()
{}


t_size Estimator_MixAlgorithm::getX( Vector * const X)
{
	*X = xPold;
	return Nx;
}

t_size Estimator_MixAlgorithm::getP( Vector * const P)
{
	*P = pPold;
	return Np;
}

t_float Estimator_MixAlgorithm::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
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
			Lxold( kk, 1 ) = 1E5 * Cell->sxW( kk, kk );

	told    = tnew;

	return (t_float) 0.0;
}


t_float Estimator_MixAlgorithm::step( Vector &unew, Vector &yXPnew, t_float tnew )
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

	Cell->g0( xMnew, pPold, unew, deltat, &g0new );

	try {
			Vector xcorr = Matrix( Nx, 1 );
			xcorr = Lxold*(yXPnew - g0new);
		    xPnew = xMnew + xcorr;
	} catch( Exception& Ex ) { throw Ex; }

	Cell->CoerceState( &xPnew );

    xPold = xPnew;
    told    = tnew;


	told = tnew;
    return (t_float) 0;
}


#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_MixAlgorithm::getLx( Vector * const Lx )
{
	*Lx = Lxold;
	return Nx;
}
#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_MixAlgorithm::getLp( Vector * const Lp )
{
	*Lp = Matrix( Matrix::Zeros, Np, Ny );
	return Np;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_MixAlgorithm::getSx( Vector * const Sx )
{
	return (t_size) 0;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_MixAlgorithm::getSp( Vector * const Sp )
{
	return (t_size) 0;
}
#endif
