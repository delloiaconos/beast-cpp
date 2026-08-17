/*
 * Estimator_EKFstate.h
 *
 *  Created on: 04/mag/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ESTIMATOR_EKFSTATE_H__
#define __ESTIMATOR_EKFSTATE_H__

#include <beast/estimators/Estimator.h>
#include <beast/cell_models/CellModel.h>

#include <beast/estimators/Estimator_EKFstate_debug.h>


class Estimator_EKFstate : public Estimator
{
public:
	Estimator_EKFstate();
	Estimator_EKFstate( CellModel * myCell );

	~Estimator_EKFstate();

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

	Matrix sxPold;

};


#endif // __ESTIMATOR_EKFSTATE_H__
