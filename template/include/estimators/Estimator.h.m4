changequote(`$', `$')dnl
changecom()dnl

// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "$$BEAST_NAME$$" header file.
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

#ifndef __ESTIMATOR_$$BEAST_UPNAME$$_H__
#define __ESTIMATOR_$$BEAST_UPNAME$$_H__

#include <$$BEAST_INCLUDE_BASEPATH$$/Estimator.h>

#include <beast/common/architecture.h>
#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

/**
 * @brief Skeleton implementation of the BEAST_NAME estimator.
 *
 * @note Replace the generated method bodies with the estimator algorithm.
 */
class $$BEAST_CLASS_NAME$$ : public Estimator
{
public:
    $$BEAST_CLASS_NAME$$ ();
    explicit $$BEAST_CLASS_NAME$$ (CellModel* cell);
    ~$$BEAST_CLASS_NAME$$ () override;

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

private:
    Vector x_;
    Vector p_;
    Vector u_;
};

#endif // __ESTIMATOR_$$BEAST_UPNAME$$_H__
