// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "Kalman Filter" header file.
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

#ifndef __ESTIMATOR_EKFSTATE_H__
#define __ESTIMATOR_EKFSTATE_H__

#include <beast/common/Debug.h>

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

#if DBGCHK_EKFSTATE( DBGMSK_EKFSTATE_ENABLE )
private:  
    Debug dbg{"[Estimator_EKFstate] ", "Estimator_EKFstate.log"};
#endif // DBGMSK_EKFSTATE_ENABLE

private:
	Vector pPold;
	Vector xPold;
	Vector uold;

	Matrix sxPold;

};


#endif // __ESTIMATOR_EKFSTATE_H__
