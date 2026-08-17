changequote(`$', `$')dnl
changecom()dnl

// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "$$BEAST_NAME$$" header file.
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

#ifndef __CELL_MODEL_$$BEAST_UPPER_NAME$$_H__
#define __CELL_MODEL_$$BEAST_UPPER_NAME$$_H__

#include <beast/common/architecture.h>
#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

#include <$$BEAST_INCLUDE_BASEPATH$$/CellModel.h>

/**
 * @brief Skeleton implementation of the BEAST_NAME cell model.
 *
 * @note Replace the generated placeholder dimensions and method bodies with
 *       the equations and constraints of the actual model.
 */
class $$BEAST_CLASS_NAME$$ : public CellModel
{
public:
    $$BEAST_CLASS_NAME$$();

#if _ARCHITECTURE_ == ARCH_PC
    explicit $$BEAST_CLASS_NAME$$(char* basepath);
#endif

    ~$$BEAST_CLASS_NAME$$() override;

    t_size f0(const Vector& xold, const Vector& pold, const Vector& uold,
              t_float deltat, Vector* const xnew) override;
    t_size f1x(const Vector& xold, const Vector& pold, const Vector& uold,
               t_float deltat, Matrix* const dnew) override;
    t_size f1p(const Vector& xold, const Vector& pold, const Vector& uold,
               t_float deltat, Matrix* const dnew) override;

    t_size g0(const Vector& xold, const Vector& pold, const Vector& uold,
              t_float deltat, Vector* const ynew) override;
    t_size g1x(const Vector& xold, const Vector& pold, const Vector& uold,
               t_float deltat, Matrix* const dnew) override;
    t_size g1p(const Vector& xold, const Vector& pold, const Vector& uold,
               t_float deltat, Matrix* const dnew) override;

    t_size CoercePars(Vector* const pp) override;
    t_size CoerceState(Vector* const xx) override;
};

#endif // __CELL_MODEL_$$BEAST_UPPER_NAME$$_H__
