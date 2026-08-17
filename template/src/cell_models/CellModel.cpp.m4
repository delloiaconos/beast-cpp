changequote(`$', `$')dnl
changecom()dnl

// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "$$BEAST_NAME$$" implementation.
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

#include <$$BEAST_INCLUDE_BASEPATH$$/CellModel.h>
#include <$$BEAST_INCLUDE_BASEPATH$$/$$BEAST_CLASS_NAME$$.h>
#include <$$BEAST_INCLUDE_BASEPATH$$/$$BEAST_CLASS_NAME$$_debug.h>

$$BEAST_CLASS_NAME$$::$$BEAST_CLASS_NAME$$()
{
    // TODO: Set the actual model dimensions.
    Nx = 0;
    Np = 0;
    Nu = 0;
    Ny = 0;

    // TODO: Initialize sxW, sxV, spR and spE for the model.
}

#if _ARCHITECTURE_ == ARCH_PC
$$BEAST_CLASS_NAME$$::$$BEAST_CLASS_NAME$$(char* basepath)
    : CellModel(basepath)
{
    // TODO: Set the actual model dimensions and load model data from basepath.
    Nx = 0;
    Np = 0;
    Nu = 0;
    Ny = 0;
}
#endif

$$BEAST_CLASS_NAME$$::~$$BEAST_CLASS_NAME$$() = default;

t_size $$BEAST_CLASS_NAME$$::f0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const xnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)xnew;
    // TODO: Implement the state-transition function.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::f1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const dnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)dnew;
    // TODO: Implement the state Jacobian df/dx.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::f1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const dnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)dnew;
    // TODO: Implement the parameter Jacobian df/dp.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::g0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const ynew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)ynew;
    // TODO: Implement the output function.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::g1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const dnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)dnew;
    // TODO: Implement the output Jacobian dg/dx.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::g1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const dnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)dnew;
    // TODO: Implement the output Jacobian dg/dp.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::CoercePars(Vector* const pp)
{
    (void)pp;
    // TODO: Constrain model parameters to their valid domain.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::CoerceState(Vector* const xx)
{
    (void)xx;
    // TODO: Constrain model states to their valid domain.
    return static_cast<t_size>(0);
}
