/*
 * Estimator_EnhancedMixAlgorithm.h
 *
 *  Created on: 04/mag/2014
 *      Author: salvatoredelloiacono
 */

#ifndef __ESTIMATOR_ENHANCEDMIXALGORITHM_H__
#define __ESTIMATOR_ENHANCEDMIXALGORITHM_H__

#include <beast/estimators/Estimator.h>
#include <beast/cell_models/CellModel.h>

#include <beast/estimators/Estimator_EnhancedMixAlgorithm_debug.h>


class Estimator_EnhancedMixAlgorithm : public Estimator
{
public:
	Estimator_EnhancedMixAlgorithm();
	Estimator_EnhancedMixAlgorithm( CellModel * myCell );

	~Estimator_EnhancedMixAlgorithm();

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
	Vector Lxold;
	Vector Lpold;
};


#endif // __ESTIMATOR_ENHANCEDMIXALGORITHM_H__
