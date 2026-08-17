// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Abstract Estimator class header file.
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
 * <REPOSITORY_URL>
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef __ESTIMATOR_H__
#define __ESTIMATOR_H__


#include <beast/cell_models/CellModel.h>

#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

#include <beast/common/architecture.h>

#define ESTIMATOR_GET_GAINS 1
#define ESTIMATOR_GET_COV	1


class Estimator
{
public:
	Estimator();
	Estimator( CellModel * cell );

	virtual ~Estimator();

	virtual t_float initialize( Vector &x0, Vector &p0, Vector &unew, Vector &yXPnew, t_float tnew );
	virtual t_float step( Vector &unew, Vector &yXPnew, t_float tnew ); // make an update with: Input U, Measurements M

	virtual t_size getX( Vector * const X ); // returns state matrix (should be a vector)
	virtual t_size getP( Vector * const P ); // returns parameters matrix (should be a vector)

#ifdef ESTIMATOR_GET_GAINS
public:
	virtual t_size getLx( Vector * const Lx ); // returns State Gain
	virtual t_size getLp( Vector * const Lp ); // returns Parameters Gain
#endif

#ifdef ESTIMATOR_GET_GAINS
public:
	virtual t_size getSx( Vector * const Sx ); // returns State Gain
	virtual t_size getSp( Vector * const Sp ); // returns Parameters Gain
#endif

public:
	CellModel * Cell;

	t_float told;

	t_size Nx;
	t_size Np;
	t_size Nu;
	t_size Ny;

};

#endif //__ESTIMATOR_H__
