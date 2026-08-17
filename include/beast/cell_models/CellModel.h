/* 
 * Modified by SDI 2013-10-10
 * Created by Salvatore Dello Iacono 2013-10-09
 */
 
#ifndef __CELL_MODEL_H__
#define __CELL_MODEL_H__

#include <beast/cell_models/CellModel_debug.h>

#include <beast/common/architecture.h>

#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

#if _ARCHITECTURE_ == ARCH_PC
	#include <string.h>
	#define CELL_MODEL_BASEPATH_LEN 250
#endif


class CellModel
{
public:
    CellModel();

#if _ARCHITECTURE_ == ARCH_PC
    CellModel( char * basepath );
    char _basepath[CELL_MODEL_BASEPATH_LEN];
#endif
    virtual ~CellModel();

    virtual t_size   f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const xnew );
    virtual t_size   f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew );
    virtual t_size   f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew );

    virtual t_size   g0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const ynew ) ;
    virtual t_size   g1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew ) ;
    virtual t_size   g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const dnew ) ;

    virtual t_size	CoercePars( Vector * const pp );
    virtual t_size	CoerceState( Vector * const xx );
    
    t_size   CheckStateDim( const Vector &xx );
    t_size   CheckParsDim( const Vector &xx );
    t_size   CheckInputDim( const Vector &xx );

public:
	t_size Nx;
	t_size Np;
	t_size Nu;
	t_size Ny;

	Matrix sxW;
	Matrix sxV;
	Matrix spR;
	Matrix spE;

	static const t_float Zero;


#ifdef DBG_CELL_MODEL_INFO
public:
	virtual t_size CellModel_Info( char * strCellModel );
#endif
};

#endif //__CELL_MODEL_H__
