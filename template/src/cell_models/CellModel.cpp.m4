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

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: $$BEAST_CLASS_NAME$$()" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

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
    (void) basepath;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: $$BEAST_CLASS_NAME$$(char* basepath)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Set the actual model dimensions and load model data from basepath.
    Nx = 0;
    Np = 0;
    Nu = 0;
    Ny = 0;
}
#endif


$$BEAST_CLASS_NAME$$::~$$BEAST_CLASS_NAME$$()
{
#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
   dbg.print( "CALL: ~$$BEAST_CLASS_NAME$$()" );
#endif
}

t_size $$BEAST_CLASS_NAME$$::f0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const xnew)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)xnew;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: f0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const xnew)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Implement the state-transition function.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::f1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)res;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: f1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Implement the state Jacobian df/dx.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::f1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)res;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: f1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

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

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: g0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const ynew)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Implement the output function.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::g1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)res;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: g1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Implement the output Jacobian dg/dx.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::g1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
    (void)xold;
    (void)pold;
    (void)uold;
    (void)deltat;
    (void)res;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: g1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Implement the output Jacobian dg/dp.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::CoercePars(Vector* const pp)
{
    (void)pp;
#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: CoerceState(Vector* const xx)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Constrain model parameters to their valid domain.
    return static_cast<t_size>(0);
}

t_size $$BEAST_CLASS_NAME$$::CoerceState(Vector* const xx)
{
    (void)xx;

#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: CoerceState(Vector* const xx)" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS

    // TODO: Constrain model states to their valid domain.
    return static_cast<t_size>(0);
}

#if _ARCHITECTURE_ == ARCH_PC || DBGCHK_CELL_MODEL( DBGMSK_CELL_MODEL_INFO )
t_size $$BEAST_CLASS_NAME$$::Info( char * strCellModel )
{
    /* Auto generated class method. */
#if DBGCHK_$$BEAST_UPNAME$$( DBGMSK_$$BEAST_UPNAME$$_CLASS )
	dbg.print( "CALL: Info( char * strCellModel )" );
#endif // DBGMSK_$$BEAST_UPNAME$$_CLASS
	char strThisModel[] = "$$BEAST_UPNAME$$";
    
    strcpy( strCellModel, strThisModel );
	return (t_size) strlen( strThisModel );
}
#endif // ARCH_PC || DBGMSK_CELL_MODEL_INFO