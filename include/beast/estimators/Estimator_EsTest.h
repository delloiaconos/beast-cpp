
// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "EsTest" header file.
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

#ifndef __ESTIMATOR_ESTEST_H__
#define __ESTIMATOR_ESTEST_H__

#include <beast/estimators/Estimator.h>
#include <beast/estimators/Estimator_EsTest_debug.h>

#include <beast/common/architecture.h>
#include <beast/common/Debug.h>

#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

/**
 * @brief Skeleton implementation of the EsTest estimator.
 *
 * @note Replace the generated method bodies with the estimator algorithm.
 */
class Estimator_EsTest : public Estimator
{
public:
    Estimator_EsTest ();
    explicit Estimator_EsTest (CellModel* cell);
    ~Estimator_EsTest () override;

    t_float initialize(Vector& x0, Vector& p0, Vector& unew,
                       Vector& yXPnew, t_float tnew) override;
    t_float step(Vector& unew, Vector& yXPnew, t_float tnew) override;

    t_size getX(Vector* const x) override;
    t_size getP(Vector* const p) override;

#ifdef ESTIMATOR_GET_GAINS
    t_size getLx(Vector* const lx) override;
    t_size getLp(Vector* const lp) override;
#endif

#ifdef ESTIMATOR_GET_COV
    t_size getSx(Vector* const sx) override;
    t_size getSp(Vector* const sp) override;
#endif

#if DBGCHK_ESTEST( DBGMSK_ESTEST_ENABLE )
private:  
    Debug dbg{"[Estimator_EsTest] ", "Estimator_EsTest.log"};
#endif // DBGMSK_ESTEST_ENABLE

private:
	Vector xPold;
    Vector pPold;
};

#endif // __ESTIMATOR_ESTEST_H__
