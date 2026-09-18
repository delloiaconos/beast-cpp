// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "R0-A1B1" implementation.
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

#include <beast/cell_models/CellModel.h>
#include <beast/cell_models/CellModel_R0A1B1.h>
#include <beast/cell_models/CellModel_R0A1B1_debug.h>

#include <beast/numerics/interpolation.h>
#include <beast/io/ModelDataLoader.h>

CellModel_R0A1B1::CellModel_R0A1B1()
{

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: CellModel_R0A1B1()" );
#endif // DBGMSK_R0A1B1_CLASS

   Nx = 2;
   Np = 3;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);

/* Initialize */
#if !ARCH_CHKTYPE( ARCH_PC )
   /* TODO: Initialize corrects values! */
   sxW.setv( 1, 1, 1.0e-4 );
   sxW.setv( 2, 2, 1.0e-6 );

   sxV.setv( 1, 1, 1.0e-6 );

   spR.setv( 1, 1, 1.0e-10 );
   spR.setv( 2, 2, 1.0e-10 );
   spR.setv( 2, 2, 1.0e-10 );

   spE.setv( 1, 1, 1.0e-6 );


   eta 		= 1.0;
   Qnom 	= 1.1*3600;

   #include "LiFePO4_ocv0.txt"
   #include "LiFePO4_ocv1.txt"

   // Define here lutlen
   lutlen 	= 101;
   for( unsigned short ii = 0; ii < lutlen; ii++ ) {
	   lutsoc[ii] 	= (float) ii*0.01;
	   lutocv0[ii]	= LUT_ocv0[ii];
	   lutocv1[ii]	= LUT_ocv1[ii];
   }

#endif // !ARCH_PC

}

#if ARCH_CHKTYPE( ARCH_PC )
CellModel_R0A1B1::CellModel_R0A1B1(const char* basepath)
    : CellModel(basepath)
{

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: CellModel_R0A1B1(const char* basepath)" );
#endif // DBGMSK_R0A1B1_CLASS

   if( basepath != (char*) NULL )
	   strcpy( _basepath, basepath );

   Nx = 2;
   Np = 3;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);

   /* Read data from file */
    beast::io::ModelDataLoader loader( basepath );

    loader.readDiagonal( "MD_COV_sxWvec.in", sxW );
    loader.readDiagonal( "MD_COV_sxVvec.in", sxV );
    loader.readDiagonal( "MD_COV_spRvec.in", spR );
    loader.readDiagonal( "MD_COV_spEvec.in", spE );

    Qnom = loader.readScalar("MD_pfix_Qn_Ah.in") * 3600.0;
    eta = loader.readScalar("MD_pfix_eta.in");

    const auto soc = loader.readVector("MD_pfix_soc.in");

    if (soc.empty()) {
        throw std::runtime_error("SOC lookup table is empty");
    }

    if (soc.size() > R0A1B1_LUT_MAXLEN) {
        throw std::runtime_error("SOC lookup table exceeds maximum size");
    }

	lutlen = static_cast<t_size>(soc.size());

    const auto ocv0 = loader.readVector( "MD_pfix_ocv0.in", lutlen );
    const auto ocv1 = loader.readVector( "MD_pfix_ocv1.in", lutlen );

    for (t_size i = 0; i < lutlen; ++i) {
        lutsoc[i]  = soc[i];
        lutocv0[i] = ocv0[i];
        lutocv1[i] = ocv1[i];
    }

}
#endif



CellModel_R0A1B1::~CellModel_R0A1B1()
{
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
   dbg.print( "CALL: ~CellModel_R0A1B1()" );
#endif
}

t_size CellModel_R0A1B1::f0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const xnew)
{
	t_float deltaSOC;
	t_float u;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: f0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const xnew)" );
#endif // DBGMSK_R0A1B1_CLASS

    u = (t_float) uold.get(1,1);
    CoulombCountingConstant = deltat / Qnom;

    deltaSOC = CoulombCountingConstant*u;
    xnew->setv(1,1, xold.get(1,1)-deltaSOC );
    xnew->setv(2,1, pold.get(2,1)*xold.get(2,1)+pold.get(3,1)*u );

    return Nx;
}


t_size CellModel_R0A1B1::f1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) xold;
	(void) uold;
	(void) deltat;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: f1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0A1B1_CLASS

    res->setv(1,1, 1);
    res->setv(1,2, 0);
    res->setv(2,1, 0);
    res->setv(2,2, pold.get(2,1) );

    return Nx*Np;
}

t_size CellModel_R0A1B1::f1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) pold;
	(void) deltat;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: f1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0A1B1_CLASS

    res->setv(1,1, 0);
    res->setv(1,2, 0);
    res->setv(1,3, 0);
    res->setv(2,1, 0);
    res->setv(2,2, xold.get(2,1) );
    res->setv(2,3, uold.get(1,1) );

	return Nx*Np;
}


t_size CellModel_R0A1B1::g0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const ynew)
{
	(void) deltat;
    
	t_float ocv0old;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: g0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const ynew)" );
#endif // DBGMSK_R0A1B1_CLASS

    ocv0old = interpxy( lutsoc, lutocv0, lutlen, xold.get( 1, 1 ) );

    ynew->setv(1,1, ocv0old - pold.get(1,1)*uold.get(1,1)+xold.get(2,1));
    return Nu;
}


t_size	CellModel_R0A1B1::CoerceState(Vector* const xx)
{
	t_size cnt = 0;
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: CoerceState(Vector* const xx)" );
#endif // DBGMSK_R0A1B1_CLASS

	if( xx->get(1,1) > (t_float) 1 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	    dbg.print( "WARNING: state x(1,1)=SOC>1. CORRECTED TO 1" );
#endif
	    cnt++;
	} else if( xx->get(1,1) < (t_float) 0.0 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	    dbg.print( "WARNING: state x(1,1)=SOC<0. CORRECTED TO ZERO" );
#endif
	    cnt++;
	}

	return cnt;
}



t_size CellModel_R0A1B1::g1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) pold;
	(void) uold;
	(void) deltat;

	t_float ocv1old;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: g1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0A1B1_CLASS

    ocv1old = interpxy( lutsoc, lutocv1, lutlen, xold.get( 1, 1 ) );

    res->setv(1,1, ocv1old );
    res->setv(1,2, 1);

    return Nu*Nx;
}


t_size CellModel_R0A1B1::g1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) xold;
	(void) pold;
	(void) deltat;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: g1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0A1B1_CLASS

    res->setv(1,1, -uold.get(1,1) );
    res->setv(1,2, 0);
    res->setv(1,3, 0);

    return Nu*Np;
}


t_size	CellModel_R0A1B1::CoercePars(Vector* const pp)
{
	t_size cnt = 0;

#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_CLASS )
	dbg.print( "CALL: CoerceState(Vector* const xx)" );
#endif // DBGMSK_R0A1B1_CLASS

	if( pp->get(1,1) <= (t_float) 0.0 ) {
	      pp->setv(1,1, CellModel::CellModel::Zero );
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	      dbg.print( "WARNING: parameter p(1,1)=R0<=0 CORRECTED TO ZERO" );
#endif
	      cnt++;
	}

	if( pp->get(2,1) < (t_float) 0.0 ) {
	      pp->setv(2,1, CellModel::CellModel::Zero );
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	      dbg.print( "WARNING: parameter p(2,1)=A1<=0 CORRECTED TO ZERO" );
#endif
	      cnt++;
	} else if( pp->get(2,1) > (t_float) 1.0) {
	      pp->setv(2,1, 1 );
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	      dbg.print( "WARNING: parameter p(2,1)=A1<1 CORRECTED TO 1" );
#endif
	      cnt++;
	}

	if( pp->get(3,1) > (t_float) 0.0 )
	{
	      pp->setv(3,1, -CellModel::Zero );
#if DBGCHK_R0A1B1( DBGMSK_R0A1B1_COERCE )
	      dbg.print( "WARNING: parameter p(3,1)=B1>=0 CORRECTED TO -ZERO" );
#endif
	      cnt++;
	}

	return cnt;
}


#if ARCH_CHKTYPE( ARCH_PC ) || DBGCHK_CELL_MODEL( DBGMSK_CELL_MODEL_INFO )
t_size CellModel_R0A1B1::Info( char * strCellModel )
{
	/* AUTO genereted Class Member */
	char strThisModel[] = "R0A1B1";
    
    strcpy( strCellModel, strThisModel );
	return (t_size) strlen( strThisModel );
}
#endif // ARCH_PC || DBGMSK_CELL_MODEL_INFO