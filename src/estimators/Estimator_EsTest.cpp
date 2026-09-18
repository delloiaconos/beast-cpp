// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "EsTest" implementation.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author Salvatore Dello Iacono
 * @date 2026
 *
 * @par Project
 * BEAST - Battery Estimation Architecture and Simulation Toolkit
 *
 * @par Repository
 * https://github.com/delloiaconos/beast-cpp.git
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */

#include <beast/estimators/Estimator.h>
#include <beast/estimators/Estimator_EsTest.h>
#include <beast/estimators/Estimator_EsTest_debug.h>

Estimator_EsTest::Estimator_EsTest()
    : Estimator()
{
}

Estimator_EsTest::Estimator_EsTest(CellModel* cell)
    : Estimator(cell),
      xPold(Nx, 1),
      pPold(Np, 1)
{
}

Estimator_EsTest::~Estimator_EsTest() = default;

t_float Estimator_EsTest::initialize(Vector& x0, Vector& p0, Vector& unew,
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

t_float Estimator_EsTest::step(Vector& unew, Vector& yXPnew, t_float tnew)
{
    (void) unew;
    (void) yXPnew;
    (void) tnew;
    
    // TODO: Implement one estimator update step.
    return static_cast<t_float>(0.0);
}

t_size Estimator_EsTest::getX(Vector* const x)
{
    /* Auto generated State getter. */

    if (x != nullptr) {
        *x = xPold;
    }
    return Nx;
}

t_size Estimator_EsTest::getP(Vector* const p)
{   
    /* Auto generated Parameters getter. */

    if (p != nullptr) {
        *p = pPold;
    }
    return Np;
}

#ifdef ESTIMATOR_GET_GAINS
t_size Estimator_EsTest::getLx(Vector* const lx)
{
    (void) lx;

    // TODO: Return the state gain when supported by the estimator.
    return static_cast<t_size>(0);
}

t_size Estimator_EsTest::getLp(Vector* const lp)
{
    (void) lp;

    // TODO: Return the parameter gain when supported by the estimator.
    return static_cast<t_size>(0);
}
#endif

#ifdef ESTIMATOR_GET_COV
t_size Estimator_EsTest::getSx(Vector* const sx)
{
    (void) sx;

    // TODO: Return the state covariance when supported by the estimator.
    return static_cast<t_size>(0);
}

t_size Estimator_EsTest::getSp(Vector* const sp)
{
    (void) sp;

    // TODO: Return the parameter covariance when supported by the estimator.
    return static_cast<t_size>(0);
}
#endif
