// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "R0-A1B1" header file.
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
 * https://github.com/delloiaconos/beast-cpp.git
 *
 * @copyright
 * Copyright (c) 2026 Salvatore Dello Iacono.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef __CELLMODEL_R0A1B1_H__
#define __CELLMODEL_R0A1B1_H__

#include <beast/common/architecture.h>
#include <beast/common/Debug.h>
#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

#include <beast/cell_models/CellModel.h>
#include <beast/cell_models/CellModel_R0A1B1_debug.h>

#define R0A1B1_LUT_MAXLEN 110

class CellModel_R0A1B1 : public CellModel
{
public:
    CellModel_R0A1B1();

#if ARCH_CHKTYPE( ARCH_PC )
    explicit CellModel_R0A1B1(const char* basepath);
#endif // ARCH_PC

    ~CellModel_R0A1B1() override;

    t_size f0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const xnew);
    t_size f1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res);
    t_size f1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res);

    t_size g0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const ynew);
    t_size g1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res);
    t_size g1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res);

    t_size	CoercePars( Vector * const pp );
    t_size	CoerceState( Vector * const xx );

private:
    t_float Qnom;
    t_float eta;
    t_float CoulombCountingConstant;

    t_size  lutlen;
    t_float lutsoc[R0A1B1_LUT_MAXLEN];
    t_float lutocv0[R0A1B1_LUT_MAXLEN];
    t_float lutocv1[R0A1B1_LUT_MAXLEN];

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_ENABLE )
private:  
    Debug dbg{"[CellModel_R0A1B1] ", "CellModel_R0A1B1.log"};
#endif

#if ARCH_CHKTYPE( ARCH_PC ) || DBGCHK_CELL_MODEL( DBGMSK_CELL_MODEL_INFO )
public:
    t_size Info( char * strCellModel );
#endif // ARCH_PC || DBGMSK_CELL_MODEL_INFO

};

#endif // __CELL_MODEL_R0A1B1_H__
