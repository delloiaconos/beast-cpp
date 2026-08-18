// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator Implementation Enhanced Kalman Filter dual.
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


#include <beast/estimators/Estimator_EKFdual.h>
#include <beast/estimators/Estimator_EKFdual_debug.h>

Estimator_EKFdual::Estimator_EKFdual()
{
	Nx = (t_size) 0;
	Np = (t_size) 0;

	Nu = (t_size) 0;
	Ny = (t_size) 0;

	told 		= (t_float) 0.0;

	xPold 		= Matrix( Nx, 1 );
	pPold 		= Matrix( Np, 1 );

	spPold 		= Matrix( Np, Np );
	sxPold 		= Matrix( Nx, Nx );

	Lxold 		= Matrix( Nx, Ny );
	Lpold 		= Matrix( Np, Ny );

	dgdpold 	= Matrix( Ny, Np );
	dxMdpold	= Matrix( Nx, Np );

}

Estimator_EKFdual::Estimator_EKFdual( CellModel * myCell )
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

	spPold 		= Matrix( Np, Np );
	sxPold 		= Matrix( Nx, Nx );

	Lxold 		= Matrix( Nx, Ny );
	Lpold 		= Matrix( Np, Ny );

	dgdpold 	= Matrix( Ny, Np );
	dxMdpold	= Matrix( Nx, Np );

	told = (t_float) 0.0;
}

Estimator_EKFdual::~Estimator_EKFdual()
{};

t_float Estimator_EKFdual::initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew )
{
	(void) yXPnew;
	
	pPold   = p0;
	xPold   = x0;

	// dummy evolution for this step (fill the vector at initial position)
	spPold  = Matrix( Matrix::Zeros, Np, Np );
	sxPold  = Matrix( Matrix::Zeros, Nx, Nx );

	told   = tnew;
	uold   = unew;

	Lxold  		= Matrix( Matrix::Zeros, Nx, Ny );
	Lpold 		= Matrix( Matrix::Zeros, Np, Ny );
	dxMdpold 	= Matrix( Matrix::Zeros, Nx, Np );

	return (t_float) 0.0;
}

t_float Estimator_EKFdual::step( Vector &unew, Vector &yXPnew, t_float tnew )
{
	t_float deltat;
#if ARCH_CHKTYPE( ARCH_NIOS )
	 deltat = tnew;
#else 
	 deltat = tnew - told;
#endif 

	// (1/XX) PARAMETER - estimate time update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 1/XX ==\n");
	dbg.print( "pPold\n" );
	pPold.Print( dbg.getFile() );
#endif

	Vector pMnew = pPold;

	// (2/XX) PARAMETER - error covariance time update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 2/XX ==\n");
	dbg.print( "spPold\n" );
	spPold.Print( dbg.getFile() );
#endif

	Matrix spMnew  = spPold + Cell->spR;

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "\n" );
	spMnew.Print( dbg.getFile() );
#endif


	// (3/XX) STATE - estimate time update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 3/XX ==\n");
	dbg.print( "pMnew\n" );
	pMnew.Print( dbg.getFile() );
	dbg.print( "xPold\n");
	xPold.Print( dbg.getFile() );
#endif


	Vector xMnew = Matrix( Nx, 1 );
	Cell->f0(xPold, pMnew, uold, deltat, &xMnew );
	Cell->CoerceState(&xMnew);

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "xMnew \n" );
	xMnew.Print( dbg.getFile() );
#endif

	// (4/XX) STATE - error covariance time update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 4/XX ==\n");
#endif


	Matrix f1xold = Matrix( Nx, Nx );
	Matrix sxMnew = Matrix( Nx, Nx );


	Cell->f1x( xPold, pMnew, uold, deltat, &f1xold ); // matrix A(k-1)
	try {
		Matrix f1xoldT = Matrix( Nx, Nx );
		f1xoldT = f1xold;
		f1xoldT.Transpose();

		sxMnew  = f1xold*sxPold*f1xoldT + Cell->sxW;
	} catch( Exception& Ex ) { throw Ex; }

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "f1xold\n" );
	f1xold.Print( dbg.getFile() );
	dbg.print( "sxMnew\n" );
	sxMnew.Print( dbg.getFile() );
#endif

	// (5/XX) STATE - Kalman gain computation
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 5/XX ==\n");
#endif

	Matrix g1xnew = Matrix( Ny, Nx );
	Matrix Lxnew = Matrix( Nx, Ny );

	Cell->g1x( xMnew, pMnew, unew, deltat, &g1xnew ); // matrix Cx(k)
#if EKFDUAL_SOLMETH == EKFDUAL_SOL_INVERT
	try {
		Matrix tmp1 = Matrix( Ny, Ny );
		Matrix tmp2I = Matrix( Nx, Nx );

		Matrix g1xnewT = Matrix( Ny, Nx );
		g1xnewT = g1xnew;
		g1xnewT.Transpose();

		tmp1  = g1xnew*sxMnew*g1xnewT;
		/* Fin quando Ny = 1 e' l'inversa di una costante! */
		tmp2I = Inv( tmp1 + Cell->sxV );

		Lxnew = sxMnew*g1xnewT*tmp2I; //Kalman gain matrix
	} catch( Exception& Ex ) { throw Ex; }
#elif EKFDUAL_SOLMETH == EKFDUAL_SOLMETH_GAUSSJ
	try {
		Matrix tmp1 = Matrix( Ny, Ny );
		Matrix g1xnewT = Matrix( Ny, Nx );

		g1xnewT = g1xnew;
		g1xnewT.Transpose();

		tmp1  = g1xnew*sxMnew*g1xnewT + Cell->sxV;

		Lxnew  = sxMnew*g1xnewT;

		gaussj_xAB( tmp1, Lxnew ); //Kalman gain matrix

	} catch( Exception& Ex ) { throw Ex; }
#endif // EKFDUAL_SOLMETH

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "g1xnew\n");
	g1xnew.Print( dbg.getFile() );

	dbg.print( "Lxnew\n" );
	Lxnew.Print( dbg.getFile() );
#endif


	 // (6/XX) STATE - estimate measurement update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 6/XX ==\n");
#endif

	Vector g0new = Matrix( Ny, 1 );
	Vector xPnew = Matrix( Nx, 1 );

	Cell->g0( xMnew, pMnew, unew, deltat, &g0new );

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "g0new\n" );
	g0new.Print( dbg.getFile() );
#endif

	try {
		Vector xcorr = Matrix( Nx, 1 );
		xcorr = Lxnew*(yXPnew - g0new);
	    xPnew = xMnew + xcorr;

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	    dbg.print( "xPnew" );
	    xPnew.Print( dbg.getFile() );
#endif

	    Cell->CoerceState( &xPnew );
	} catch( Exception& Ex ) { throw Ex; }

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "xPnew\n" );
	xPnew.Print( dbg.getFile() );
#endif



	// (7/XX) STATE - error covariance measurement update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 7/XX ==\n");
#endif

	Matrix sxPnew = Matrix( Nx, Nx );

	try {
		Matrix eyeNx = Matrix( Matrix::Identity, Nx, Nx );
	    sxPnew = (eyeNx-Lxnew*g1xnew)*sxMnew;
	} catch( Exception& Ex ) { throw Ex; }

    // (8/XX) PARAMETER - Kalman gain computation
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 8/XX ==\n");
#endif

	Matrix g1pnew 	= Matrix( Ny, Np );
	Matrix f1pold 	= Matrix( Nx, Np );
    Matrix dxPdpold = Matrix( Nx, Np );
    Matrix dxMdpnew = Matrix( Nx, Np );
    Matrix dgdpnew 	= Matrix( Ny, Np );
    Vector Lpnew 	= Matrix( Np, Ny );

    Cell->g1p( xMnew, pMnew, unew, deltat, &g1pnew );
    Cell->f1p( xPold, pMnew, uold, deltat, &f1pold );

    try {
    	dxPdpold = dxMdpold - Lxold*dgdpold;
    	dxMdpnew = f1pold + f1xold*dxPdpold;
    	dgdpnew  = g1pnew + g1xnew*dxMdpnew;
    } catch( Exception& Ex ) { throw Ex; }

#if EKFDUAL_SOLMETH == EKFDUAL_SOL_INVERT
    try {
    	Matrix tmp1 = Matrix( Np, Np );
    	Matrix tmp2I = Matrix( Np, Np );
    	Matrix dgdpnewT = Matrix( Ny, Np );

    	dgdpnewT = dgdpnew;
    	dgdpnewT.Transpose();

    	tmp1  = dgdpnew*spMnew*dgdpnewT;
    	tmp2I = Inv( tmp1 + Cell->spE );

    	Lpnew = spMnew*dgdpnewT*tmp2I;
    } catch( Exception& Ex ) { throw Ex; }
#elif EKFDUAL_SOLMETH == EKFDUAL_SOLMETH_GAUSSJ
    try {
    	Matrix tmp1 = Matrix( Np, Np );
    	Matrix dgdpnewT = Matrix( Ny, Np );

    	dgdpnewT = dgdpnew;
    	dgdpnewT.Transpose();

    	tmp1  = dgdpnew*spMnew*dgdpnewT + Cell->spE;

    	Lpnew = spMnew*dgdpnewT;

    	gaussj_xAB( tmp1, Lpnew ); // Solve for Lpnew
    } catch( Exception& Ex ) { throw Ex; }
#endif //EKFDUAL_SOLMETH


    // (9/XX) PARAMETER - estimate measurement update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 9/XX ==\n");
#endif

    Vector pPnew = Matrix( Np, 1 );

    try{
    	Vector pcorr = Matrix( Np, 1 );
    	pcorr = Lpnew*(yXPnew - g0new);
    	pPnew = pMnew + pcorr;
    	Cell->CoercePars( &pPnew );
    } catch( Exception& Ex ) { throw Ex; }


    // (10/10) PARAMETERS - error covariance measurement update
#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
	dbg.print( "== 10/XX ==\n");
#endif

    Matrix spPnew = Matrix( Np, Np );

    try {
    	Matrix eyeNp = Matrix( Matrix::Identity, Np, Np );
    	spPnew = (eyeNp-Lpnew*dgdpnew)*spMnew;
    } catch( Exception& Ex ) { throw Ex; }

    // preparing next step
    told   = tnew;
    uold   = unew;

    pPold    = pPnew;
    spPold   = spPnew;
    xPold    = xPnew;
    sxPold   = sxPnew;
    dxMdpold = dxMdpnew;
    Lxold    = Lxnew;
    Lpold 	 = Lpnew;
    dgdpold  = dgdpnew;

#if DBGCHK_EKFDUAL( DBGMSK_EKFDUAL_STEPBYSTEP )
    dbg.print( "sxPold\n");
    sxPold.Print( dbg.getFile() );
#endif

    return (t_float) 0;
}


t_size Estimator_EKFdual::getX( Vector * const X)
{
	*X = xPold;
	return Nx;
}

t_size Estimator_EKFdual::getP( Vector * const P)
{
	*P = pPold;
	return Np;
}


#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EKFdual::getLx( Vector * const Lx )
{
	*Lx = Lxold;
	return Nx;
}
#endif

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EKFdual::getLp( Vector * const Lp )
{
	*Lp = Lpold;
	return Np;
}
#endif



#ifdef ESTIMATOR_GET_COV
t_size Estimator_EKFdual::getSx( Vector * const Sx )
{
	*Sx = sxPold;
	return Nx*Nx;
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_EKFdual::getSp( Vector * const Sp )
{
	*Sp = spPold;
	return Np*Np;
}
#endif


