// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Abstract Class Cell Model.
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

#include <beast/cell_models/CellModel.h>
#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

const t_float CellModel::Zero = 1e-9;


CellModel::CellModel()
{/*
	Nx = 0;
	Np = 0;
	Nu = 0;
	Ny = 0;
	sxW = Matrix(Nx, Nx);
	sxV = Matrix(Ny, Ny);
	spR = Matrix(Np, Np);
	spE = Matrix(Ny, Ny);*/
}

CellModel::~CellModel()
{}

#if _ARCHITECTURE_ == ARCH_PC
CellModel::CellModel( char * basepath )
{
/*	strcpy( _basepath, basepath );
	Nx = 0;
	Np = 0;
	Nu = 0;
	Ny = 0;
	sxW = Matrix(Nx, Nx);
	sxV = Matrix(Ny, Ny);
	spR = Matrix(Np, Np);
	spE = Matrix(Ny, Ny);*/
}
#endif //_ARCHITECTURE_ == ARCH_PC

t_size CellModel::f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const xnew )
{
	return (t_size) 0;
}

t_size CellModel::f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew )
{
	return (t_size) 0;
}

t_size CellModel::f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew )
{
	return (t_size) 0;
}

t_size CellModel::g0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const ynew )
{
	return (t_size) 0;
}

t_size CellModel::g1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew )
{
	return (t_size) 0;
}

t_size CellModel::g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew )
{
	return (t_size) 0;
}

t_size CellModel::CoercePars( Vector * const pp )
{
	return (t_size) 0;
}

t_size CellModel::CoerceState( Vector * const xx )
{
	return (t_size) 0;
}



t_size CellModel::CheckParsDim( const Vector &pp )
{
	if( pp.GetRows() != Np )
		return 1;

	if( pp.GetCols() != (t_size) 1 )
		return 2;

	return (t_size) 0;
}

t_size CellModel::CheckStateDim( const Vector &xx )
{
	if( xx.GetRows() != Nx )
			return (t_size) 1;

	if( xx.GetCols() != (t_size) 1 )
			return (t_size) 2;

	return (t_size) 0;
}

t_size CellModel::CheckInputDim( const Vector &uu )
{
	if( uu.GetRows() != Nu )
			return (t_size) 1;

	if( uu.GetCols() != (t_size) 1 )
			return (t_size) 2;

	return (t_size) 0;
}


#ifdef DBGMSK_CELL_MODEL_INFO
t_size CellModel::CellModel_Info( char * strCellModel );
{
	*strCellModel = '\0';
	return (t_size) 0;
}
#endif
