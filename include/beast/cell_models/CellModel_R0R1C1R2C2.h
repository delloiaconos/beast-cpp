/* 
 * Class Header File: CellModel_R0R1C1R2C2
 * Created by Salvatore Dello Iacono Ven 12-Dic-2014 18:00
 *
 */

#ifndef __CELLMODEL_R0R1C1R2C2_H__
#define __CELLMODEL_R0R1C1R2C2_H__


#include <beast/cell_models/CellModel.h>
#include <beast/cell_models/CellModel_debug.h>

#include <beast/cell_models/CellModel_R0R1C1R2C2_debug.h>

#include <beast/common/architecture.h>

#include <beast/numerics/Vector.h>
#include <beast/numerics/Matrix.h>

#include <math.h>

#define R0R1C1R2C2_LUT_MAXLEN 110

class CellModel_R0R1C1R2C2 : public CellModel
{
      
public: 
	CellModel_R0R1C1R2C2();
	
#if _ARCHITECTURE_ == ARCH_PC
	CellModel_R0R1C1R2C2( char * basepath );
#endif

	~CellModel_R0R1C1R2C2();
    
    t_size   f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const xnew );
    t_size   f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res );
    t_size   f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res ) ;

    t_size   g0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const ynew ) ;
    t_size   g1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res ) ;
    t_size   g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res ) ;

    t_size	CoercePars( Vector * const pp );
    t_size	CoerceState( Vector * const xx );

#if R0R1C1R2C2_DBG( DBG_R0R1C1R2C2_ENB )
private:  
    void inline CellModel_DebugInit( void );
    FILE * fdbg;
#endif

#if _ARCHITECTURE_ == ARCH_PC || defined DBG_CELL_MODEL_INFO
public:
	t_size CellModel_Info( char * strCellModel );
#endif 

private:
    t_float Qnom;
    t_float eta;
    t_float CoulombCountingConstant;

    t_size  lutlen;
    t_float lutsoc[R0R1C1R2C2_LUT_MAXLEN];
    t_float lutocv0[R0R1C1R2C2_LUT_MAXLEN];
    t_float lutocv1[R0R1C1R2C2_LUT_MAXLEN];

};



#endif //__CELLMODEL_R0R1C1R2C2_H__
