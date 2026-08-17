/*
 * Estimator_EKFdual.h
 *
 *  Created on: 04/mag/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ESTIMATOR_EKFDUAL_H__
#define __ESTIMATOR_EKFDUAL_H__

#include <beast/estimators/Estimator.h>
#include <beast/cell_models/CellModel.h>

#include <beast/estimators/Estimator_EKFdual_debug.h>


/* Gain Solution Method: */
#define EKFDUAL_SOLMETH_INVERT 1 // Invert the matrix
#define EKFDUAL_SOLMETH_GAUSSJ 2 // Solve with Gauss-Jordan elimination

#define EKFDUAL_SOLMETH EKFDUAL_SOL_GAUSSJ


class Estimator_EKFdual : public Estimator
{
public:
	Estimator_EKFdual();
	Estimator_EKFdual( CellModel * myCell );

	~Estimator_EKFdual();

	t_float initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew );
	t_float step( Vector &unew, Vector &yXPnew, t_float tnew );

	t_size getX( Vector * const X );
	t_size getP( Vector * const P );

#ifdef ESTIMATOR_GET_GAINS
public:
	t_size getLx( Vector * const Lx );
	t_size getLp( Vector * const Lp );
#endif

#ifdef ESTIMATOR_GET_COV
public:
	t_size getSx( Vector * const Sx ); // returns State Gain
	t_size getSp( Vector * const Sp ); // returns Parameters Gain
#endif

private:

	Vector pPold;
	Vector xPold;
	Vector uold;

	Matrix spPold;
	Matrix sxPold;

	Matrix Lxold;
	Matrix Lpold;

	Matrix dgdpold;
	Matrix dxMdpold;

};


#endif // __ESTIMATOR_EKFDUAL_H__
