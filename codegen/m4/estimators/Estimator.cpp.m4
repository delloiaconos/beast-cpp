changequote(`$', `$')dnl
changecom()dnl
// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "$$BEAST_NAME$$" implementation.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author $$BEAST_AUTHOR$$
 * @date $$BEAST_YEAR$$
 *
 * @par Project
 * BEAST - Battery Estimation Architecture and Simulation Toolkit
 *
 * @par Repository
 * $$BEAST_REPOSITORY$$
 *
 * @copyright
 * Copyright (c) $$BEAST_YEAR$$ $$BEAST_AUTHOR$$.
 *
 * @license
 * GNU General Public License v3.0.
 */

#include <$$BEAST_INCLUDE_BASEPATH$$/Estimator.h>
#include <$$BEAST_INCLUDE_BASEPATH$$/$$BEAST_CLASS_NAME$$.h>
#include <$$BEAST_INCLUDE_BASEPATH$$/$$BEAST_CLASS_NAME$$_debug.h>

$$BEAST_CLASS_NAME$$::$$BEAST_CLASS_NAME$$()
    : Estimator()
{
}

$$BEAST_CLASS_NAME$$::$$BEAST_CLASS_NAME$$(CellModel* cell)
    : Estimator(cell),
      xPold(Nx, 1),
      pPold(Np, 1)
{
}

$$BEAST_CLASS_NAME$$::~$$BEAST_CLASS_NAME$$() = default;

t_float $$BEAST_CLASS_NAME$$::initialize(Vector& x0, Vector& p0, Vector& unew,
                                      Vector& yXPnew, t_float tnew)
{
    (void) unew;
    (void) yXPnew;
    (void) tnew;

    xPold = x0;
    pPold = p0;

    // TODO: Initialize estimator-specific state and covariance information.
    return static_cast<t_float>(0.0);
}

t_float $$BEAST_CLASS_NAME$$::step(Vector& unew, Vector& yXPnew, t_float tnew)
{
    (void) unew;
    (void) yXPnew;
    (void) tnew;
    
    // TODO: Implement one estimator update step.
    return static_cast<t_float>(0.0);
}

t_size $$BEAST_CLASS_NAME$$::getX(Vector* const x)
{
    /* Auto generated State getter. */

    if (x != nullptr) {
        *x = xPold;
    }
    return Nx;
}

t_size $$BEAST_CLASS_NAME$$::getP(Vector* const p)
{   
    /* Auto generated Parameters getter. */

    if (p != nullptr) {
        *p = pPold;
    }
    return Np;
}

#ifdef ESTIMATOR_GET_GAINS
t_size $$BEAST_CLASS_NAME$$::getLx(Vector* const lx)
{
    (void) lx;

    // TODO: Return the state gain when supported by the estimator.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::getLp(Vector* const lp)
{
    (void) lp;

    // TODO: Return the parameter gain when supported by the estimator.
    return static_cast<t_size>(0);
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size $$BEAST_CLASS_NAME$$::getSx(Vector* const sx)
{
    (void) sx;

    // TODO: Return the state covariance when supported by the estimator.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::getSp(Vector* const sp)
{
    (void) sp;

    // TODO: Return the parameter covariance when supported by the estimator.
    return static_cast<t_size>(0);
}
#endif
