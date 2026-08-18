// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model "R0-R1C1-R2C2" implementation.
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
#include <beast/cell_models/CellModel_R0R1C1R2C2.h>
#include <beast/cell_models/CellModel_R0R1C1R2C2_debug.h>
#include <beast/numerics/interpolation.h>

CellModel_R0R1C1R2C2::CellModel_R0R1C1R2C2()
{

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: CellModel_R0R1C1R2C2()" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

   Nx = 3;
   Np = 5;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);


   /* Initialize! */
#if !ARCH_CHKTYPE( ARCH_PC )
   sxW.setv( 1, 1, 1.0e-4 );
   sxW.setv( 2, 2, 1.0e-6 );
   sxW.setv( 3, 3, 1.0e-6 );

   sxV.setv( 1, 1, 1.0e-6 );

   spR.setv( 1, 1, 1.0e-10 );
   spR.setv( 2, 2, 1.0e-10 );
   spR.setv( 3, 3, 1.0e-10 );
   spR.setv( 4, 4, 1.0e-10 );
   spR.setv( 5, 5, 1.0e-10 );

   spE.setv( 1, 1, 1.0e-6 );


   eta 		= 1.0;
   Qnom 	= 1.1*3600;

	#include "Data/LiFePO4.inc"

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
CellModel_R0R1C1R2C2::CellModel_R0R1C1R2C2(const char* basepath)
    : CellModel(basepath)
{
	FILE * fr;
	char filename[2*CELL_MODEL_BASEPATH_LEN];

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: CellModel_R0R1C1R2C2(const char* basepath)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

   Nx = 3;
   Np = 5;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);

   /* Read from file */
     try {
  	   t_float tmp;
  	   t_size i;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_COV_sxWvec.in" );
  	   fr = fopen( filename, "r" );
  	   for( i = 0; i < sxW.GetRows() && !feof(fr); i++ ) {
  	   	   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  	   	   sxW(i+1,i+1) = tmp;

  	   }
  	   fclose( fr );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_FUNDBG ) && ARCH_CHKTYPE( ARCH_PC )
  	   dbg.print( "sxW:\n" );
  	   sxW.Print( dbg.getFile() );
#endif
     } catch (const Exception& Ex) {}

     try {
  	   t_float tmp;
  	   t_size i;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_COV_sxVvec.in" );
  	   fr = fopen( filename, "r" );
  	   for( i = 0; i < sxV.GetRows() && !feof(fr); i++ ) {
  	   	   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  	   	   sxV(i+1,i+1) = tmp;
  	   }
  	   fclose( fr );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_FUNDBG ) && ARCH_CHKTYPE( ARCH_PC )
  	   dbg.print( "sxV:\n" );
  	   sxV.Print( dbg.getFile() );
#endif
     } catch (const Exception& Ex) {}

     try {
  	   t_float tmp;
  	   t_size i;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_COV_spRvec.in" );
  	   fr = fopen( filename, "r" );
  	   for( i = 0; i < spR.GetRows() && !feof(fr); i++ ) {
  	   	   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  	   	   spR(i+1,i+1) = tmp;
  	   }
  	   fclose( fr );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_FUNDBG ) && ARCH_CHKTYPE( ARCH_PC )
  	   dbg.print( "spR:\n" );
  	   spR.Print( dbg.getFile() );
#endif
     } catch (const Exception& Ex) {}

     try {
  	   t_float tmp;
  	   t_size i;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_COV_spEvec.in" );
  	   fr = fopen( filename, "r" );
  	   for( i = 0; i < spE.GetRows() && !feof(fr); i++ ) {
  	   	   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  	   	   spE(i+1,i+1) = tmp;
  	   }
  	   fclose( fr );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_FUNDBG ) && ARCH_CHKTYPE( ARCH_PC )
  	   dbg.print( "spE:\n" );
  	   spE.Print( dbg.getFile() );
#endif
     } catch (const Exception& Ex) {}

     try {
  	   // Qn_Ah
    	   t_float tmpQn;
    	   strcpy( filename, basepath );
    	   strcat( filename, "/MD_pfix_Qn_Ah.in" );
    	   fr = fopen( filename, "r" );
    	   fread( &tmpQn, sizeof(t_float), (t_size) 1, fr );
    	   Qnom = tmpQn*3600;
    	   fclose( fr );
     } catch (const Exception& Ex) {}

     try {
  	   // eta
    	   t_float tmpEta;
    	   strcpy( filename, basepath );
    	   strcat( filename, "/MD_pfix_eta.in" );
    	   fr = fopen( filename, "r" );
    	   fread( &tmpEta, sizeof(t_float), (t_size) 1, fr );
    	   eta = tmpEta;
    	   fclose( fr );
     } catch (const Exception& Ex) {}

     try {
     // lutsoc; lutlen
  	   t_float tmp;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_pfix_soc.in" );
  	   fr = fopen( filename, "r" );
  	   lutlen = 0;
  	   while( !feof(fr) && lutlen < R0R1C1R2C2_LUT_MAXLEN )
  	   {
  		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  		   lutsoc[lutlen] = tmp;
  		   lutlen++;
  	   }
  	   fclose( fr );
     } catch (const Exception& Ex) {}

     try {
  	   t_float tmp;
  	   t_size i;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_pfix_ocv0.in" );
  	   fr = fopen( filename, "r" );

  	   for( i = 0; (i < lutlen) && !feof(fr); i++ )
  	   {
  		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  		   lutocv0[i] = tmp;
  	   }

  	   fclose( fr );
     } catch (const Exception& Ex) {}

     try {
     	   t_float tmp;
     	   t_size i;
     	   strcpy( filename, basepath );
     	   strcat( filename, "/MD_pfix_ocv1.in" );
     	   fr = fopen( filename, "r" );

     	   for( i = 0; (i < lutlen) && !feof(fr); i++ )
     	   {
     		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
     		   lutocv1[i] = tmp;
     	   }
     	   fclose( fr );
     } catch (const Exception& Ex) {}

}
#endif // ARCH_PC


CellModel_R0R1C1R2C2::~CellModel_R0R1C1R2C2()
{
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
   dbg.print( "CALL: ~CellModel_R0R1C1R2C2()" );
#endif // DBGMSK_R0R1C1R2C2_CLASS
}


t_size CellModel_R0R1C1R2C2::g0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const ynew)
{
	(void) deltat;
	
	t_float ocv0old;
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: g0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const ynew)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    ocv0old  = interpxy( lutsoc, lutocv0, lutlen, xold.get(1,1));
    ynew->setv(1,1, ocv0old -pold.get(1,1)*uold.get(1,1)+xold.get(2,1) + xold.get(3,1));
    return Nu;
}


t_size CellModel_R0R1C1R2C2::g1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) pold;
	(void) uold;
	(void) deltat;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: g1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    res->setv(1,1, interpxy( lutsoc, lutocv1, lutlen, xold.get(1,1) ) );
    res->setv(1,2, (t_float) 1.0 );
    res->setv(1,3, (t_float) 1.0 );
    return Nu*Nx;
}

t_size CellModel_R0R1C1R2C2::g1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) xold;
	(void) pold;
	(void) deltat;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: g1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    res->setv(1,1, - uold.get(1,1) );
    res->setv(1,2, (t_float) 0.0 );
    res->setv(1,3, (t_float) 0.0 );
    res->setv(1,4, (t_float) 0.0 );
    res->setv(1,5, (t_float) 0.0 );

    return Nu*Np;
}

t_size CellModel_R0R1C1R2C2::f0(const Vector& xold, const Vector& pold,
                            const Vector& uold, t_float deltat,
                            Vector* const xnew)
{
	t_float deltaSOC;
	t_float tau1, alpha1;
	t_float tau2, alpha2;
	t_float u;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: f0(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Vector* const xnew)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    u = uold.get(1,1);
    CoulombCountingConstant = eta*deltat/Qnom;

    deltaSOC = CoulombCountingConstant*u;

    tau1   = pold.get(2,1)*pold.get(3,1);
    alpha1 = exp( - deltat/tau1 );

    tau2   = pold.get(4,1)*pold.get(5,1);
    alpha2 = exp( - deltat/tau2 );

    xnew->setv(1,1, xold.get(1,1)-deltaSOC );
    xnew->setv(2,1, alpha1*xold.get(2,1)+pold.get(2,1)*(alpha1 - 1.0)*u );
    xnew->setv(3,1, alpha2*xold.get(3,1)+pold.get(4,1)*(alpha2 - 1.0)*u );
    return Nx;

}

t_size CellModel_R0R1C1R2C2::f1x(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
	(void) xold;
	(void) uold;
	
	t_float tau1, alpha1;
	t_float tau2, alpha2;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: f1x(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    tau1   = pold.get(2,1)*pold.get(3,1);
    alpha1 = exp( - deltat/tau1 );

    tau2   = pold.get(4,1)*pold.get(5,1);
    alpha2 = exp( - deltat/tau2 );

    res->setv(1,1, (t_float) 1.0 ) ;
    res->setv(1,2, (t_float) 0.0 );
    res->setv(1,3, (t_float) 0.0 );

    res->setv(2,1, (t_float) 0.0 );
    res->setv(2,2, alpha1 );
    res->setv(2,3, (t_float) 0.0 );

    res->setv(3,1, (t_float) 0.0 );
    res->setv(3,2, (t_float) 0.0 );
    res->setv(3,3, alpha2 );

    return Nx*Nx;
}

t_size CellModel_R0R1C1R2C2::f1p(const Vector& xold, const Vector& pold,
                             const Vector& uold, t_float deltat,
                             Matrix* const res)
{
    t_float tau1, alpha1, adtrc1;
	t_float tau2, alpha2, adtrc2;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: f1p(const Vector& xold, const Vector& pold, const Vector& uold, t_float deltat, Matrix* const res)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    tau1   = pold.get(2,1)*pold.get(3,1);
    alpha1 = exp( - deltat/tau1 );
    adtrc1 = alpha1*deltat/tau1;

    tau2   = pold.get(4,1)*pold.get(5,1);
	alpha2 = exp( - deltat/tau2 );
	adtrc2 = alpha2*deltat/tau2;

	res->setv(1,1, (t_float) 0.0 );
	res->setv(1,2, (t_float) 0.0 );
	res->setv(1,3, (t_float) 0.0 );
	res->setv(1,4, (t_float) 0.0 );
	res->setv(1,5, (t_float) 0.0 );

	res->setv(2,1, (t_float) 0.0 );
	res->setv(2,2, adtrc1/pold.get(2,1)*xold.get(2,1)+(alpha1-1.+adtrc1)*uold.get(1,1) );
	res->setv(2,3, adtrc1/pold.get(3,1)*(xold.get(2,1)+pold.get(2,1)*uold.get(1,1)) ) ;
	res->setv(2,4, (t_float) 0.0 );
	res->setv(2,5, (t_float) 0.0 );

	res->setv(3,1, (t_float) 0.0 );
	res->setv(3,2, (t_float) 0.0 );
	res->setv(3,3, (t_float) 0.0 );
	res->setv(3,4, adtrc2/pold.get(4,1)*xold.get(3,1)+(alpha2-1.+adtrc2)*uold.get(1,1) );
	res->setv(3,5, adtrc2/pold.get(5,1)*(xold.get(3,1)+pold.get(4,1)*uold.get(1,1)) ) ;

	return Nx*Np;
}

t_size CellModel_R0R1C1R2C2::CoercePars(Vector* const pp)
{
	t_size cntCoerce = 0;
    
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: CoercePars(Vector* const pp)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

    if( pp->get(1,1) <= (t_float) 0.0 ) {
    	pp->setv(1,1, CellModel::CellModel::Zero );

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
    	dbg.print( "WARNING: parameter p(1,1)=R0<=0 CORRECTED TO ZERO" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
    	cntCoerce++;
    }

	if( pp->get(2,1) < (t_float) 0.0 ) {
		pp->setv(2,1, CellModel::CellModel::Zero );

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
		dbg.print( "WARNING: parameter p(2,1)=R1<=0 CORRECTED TO ZERO" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
        
		cntCoerce++;
	}

	if( pp->get(3,1) < (t_float) 0.0 )
	{
		pp->setv(3,1, CellModel::Zero );

    #if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
		dbg.print( "WARNING: parameter p(3,1)=C1<0 CORRECTED TO ZERO" );
    #endif // DBGMSK_R0R1C1R2C2_COERCE

		cntCoerce++;
	}

	if( pp->get(4,1) < (t_float) 0.0 )
	{
		pp->setv(4,1, CellModel::Zero );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
		dbg.print( "WARNING: parameter p(4,1)=R2<0 CORRECTED TO ZERO" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
		cntCoerce++;
	}

	if( pp->get(5,1) < (t_float) 0.0 )
	{
		pp->setv(5,1, CellModel::Zero );
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
		dbg.print( "WARNING: parameter p(5,1)=C2<0 CORRECTED TO ZERO" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
		cntCoerce++;
	}

	return cntCoerce;
}

t_size CellModel_R0R1C1R2C2::CoerceState(Vector* const xx)
{
	t_size cntCoerce = 0;

#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: CoerceState(Vector* const xx)" );
#endif // DBGMSK_R0R1C1R2C2_CLASS

	if( xx->get(1,1) > (t_float) 1 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
	    dbg.print( "WARNING: state x(1,1)=SOC>1. CORRECTED TO 1" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
	    cntCoerce++;
	} else if( xx->get(1,1) < (t_float) 0.0 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_COERCE )
	    dbg.print( "WARNING: state x(1,1)=SOC<0. CORRECTED TO ZERO" );
#endif // DBGMSK_R0R1C1R2C2_COERCE
	    cntCoerce++;
	}

    return cntCoerce;
}

#if ARCH_CHKTYPE( ARCH_PC ) || DBGCHK_CELL_MODEL( DBGMSK_CELL_MODEL_INFO )
t_size CellModel_R0R1C1R2C2::Info( char * strCellModel )
{
    /* Auto generated class method. */
#if DBGCHK_R0R1C1R2C2( DBGMSK_R0R1C1R2C2_CLASS )
	dbg.print( "CALL: Info( char * strCellModel )" );
#endif // DBGMSK_R0R1C1R2C2_CLASS
	char strThisModel[] = "R0R1C1R2C2";
    
    strcpy( strCellModel, strThisModel );
	return (t_size) strlen( strThisModel );
}
#endif // ARCH_PC || DBGMSK_CELL_MODEL_INFO