// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Cell Model Implementation R0-R1C1
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

#include <beast/cell_models/CellModel_R0R1C1.h>

#include <beast/numerics/Vector.h>
#include <beast/numerics/Matrix.h>

#include <beast/numerics/interpolation.h>

#if _ARCHITECTURE_ == ARCH_PC
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
#endif


CellModel_R0R1C1::CellModel_R0R1C1()
{
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_ENABLE )
   CellModel_DebugInit();
#endif
   
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
   CellModel_R0R1C1_dprint( "CALL: CellModel_R0R1C1()" );
#endif   

   Nx = 2;
   Np = 3;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);

   /* Initialize! */
#if _ARCHITECTURE_ != ARCH_PC
   sxW.setv( 1, 1, 1.0e-4 );
   sxW.setv( 2, 2, 1.0e-6 );

   sxV.setv( 1, 1, 1.0e-6 );

   spR.setv( 1, 1, 1.0e-10 );
   spR.setv( 2, 2, 1.0e-10 );
   spR.setv( 3, 3, 1.0e-10 );

   spE.setv( 1, 1, 1.0e-6 );


   eta 		= 1.0;
   Qnom 	= 1.1*3600;

	#include "LiFePO4_ocv0.inc"
	#include "LiFePO4_ocv1.inc"

   // Define here lutlen
   lutlen 	= 101;
   for( unsigned short ii = 0; ii < lutlen; ii++ ) {
	   lutsoc[ii] 	= (float) ii*0.01;
	   lutocv0[ii]	= LUT_ocv0[ii];
	   lutocv1[ii]	= LUT_ocv1[ii];
   }

#endif
}


#if _ARCHITECTURE_ == ARCH_PC
CellModel_R0R1C1::CellModel_R0R1C1( char * basepath )
{
	FILE * fr;
	char filename[CELL_MODEL_BASEPATH_LEN];

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_ENABLE )
   CellModel_DebugInit();
#endif
   
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
   CellModel_R0R1C1_dprint( "CALL: CellModel_R0R1C1( char * basepath )" );
#endif   

   Nx = 2;
   Np = 3;
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
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
  	   fprintf( fFun, "sxW:\n" );
  	   sxW.Print( fFun );
#endif
     } catch (const Exception& Ex) {}
     fprintf( stderr, "OK  002\n" );
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
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
  	   fprintf( fFun, "sxV:\n" );
  	   sxV.Print( fFun );
#endif
     } catch (const Exception& Ex) {}
     fprintf( stderr, "OK  003\n" );
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
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
  	   fprintf( fFun, "spR:\n" );
  	   spR.Print( fFun );
#endif
     } catch (const Exception& Ex) {}

     fprintf( stderr, "OK  004\n" );
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
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
  	   fprintf( fFun, "spE:\n" );
  	   spE.Print( fFun );
#endif
     } catch (const Exception& Ex) {}

     fprintf( stderr, "OK  005\n" );
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

     fprintf( stderr, "OK  006\n" );
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

     fprintf( stderr, "OK  007\n" );
     try {
     // lutsoc; lutlen
  	   t_float tmp;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_pfix_soc.in" );
  	   fr = fopen( filename, "r" );
  	   lutlen = 0;
  	   while( !feof(fr) && lutlen < R0R1C1_LUT_MAXLEN )
  	   {
  		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
  		   lutsoc[lutlen] = tmp;
  		   lutlen++;
  	   }
  	   fclose( fr );
     } catch (const Exception& Ex) {}

     fprintf( stderr, "OK  008\n" );
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

     fprintf( stderr, "OK  009\n" );
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
#endif // _ARCHITECTURE_ == ARCH_PC

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_ENABLE )
void inline CellModel_R0R1C1::CellModel_DebugInit( void )
{    
   fdbg = fopen( "CellModel_R0R1C1_dbg.txt", "wt" );

#if DBGCHK_R0R1C1( DBGMSK_H0F0A_CLASS )
   CellModel_R0R1C1_dprint( "CALL: CellModel_DebugInit()" );
#endif

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
   fFun = fopen( "CellModel_ROR1C1.txt", "wt" );
#endif
}
#endif


CellModel_R0R1C1::~CellModel_R0R1C1()
{
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
   CellModel_R0R1C1_dprint( "CALL: ~CellModel_R0R1C1()" );
#endif

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_FUNDBG ) && _ARCHITECTURE_ == ARCH_PC
   fclose( fFun );
#endif

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_ENABLE )
    fclose( fdbg );
#endif 

}

t_size CellModel_R0R1C1::g0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res )
{   
	(void) deltat;

	t_float ocv0old;
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: y0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const ynew )" );
#endif
    ocv0old  = interpxy( lutsoc, lutocv0, lutlen, xold.get(1,1));
    res->setv(1,1, ocv0old -pold.get(1,1)*uold.get(1,1)+xold.get(2,1) );
    return Nu;
}


t_size CellModel_R0R1C1::g1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
	(void) pold;
	(void) uold;
	(void) deltat;

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: y1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    res->setv(1,1, interpxy( lutsoc, lutocv1, lutlen, xold.get(1,1) ) );
    res->setv(1,2, (t_float) 1.0 );

    return Nu*Nx;
}

t_size CellModel_R0R1C1::g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
	(void) xold;
	(void) pold;
	(void) deltat;

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: y1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    res->setv(1,1, - uold.get(1,1) );
    res->setv(1,2, (t_float) 0.0 );
    res->setv(1,3, (t_float) 0.0 );

    return Nu*Np;
}

t_size CellModel_R0R1C1::f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res)
{
	t_float deltaSOC, tauloc, alphaloc;
	t_float u;
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const xnew )" );
#endif
    u = uold.get(1,1);
    CoulombCountingConstant = eta*deltat/Qnom;

    deltaSOC = CoulombCountingConstant*u;
    tauloc   = pold.get(2,1)*pold.get(3,1);
    alphaloc = exp( - deltat/tauloc );
    res->setv(1,1, xold.get(1,1)-deltaSOC );
    res->setv(2,1, alphaloc*xold.get(2,1)+pold.get(2,1)*(alphaloc - 1.0)*u );

    return Nx;
}

t_size CellModel_R0R1C1::f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
	(void) xold;
	(void) uold;
	 
	t_float tauloc, alphaloc;

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    tauloc   = pold.get(2,1)*pold.get(3,1);
    alphaloc = exp( - deltat/tauloc );

    res->setv(1,1, (t_float) 1.0 );
    res->setv(1,2, (t_float) 0.0 );

    res->setv(2,1, (t_float) 0.0 );
    res->setv(2,2, alphaloc );

    return Nx*Nx;
}

t_size CellModel_R0R1C1::f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
	t_float alphaloc, tauloc, adtrc;
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    tauloc   = pold.get(2,1)*pold.get(3,1);
    alphaloc = exp(- deltat/tauloc );
    adtrc    = alphaloc*deltat/tauloc;
    res->setv(1,1, (t_float) 0.0 );
    res->setv(1,2, (t_float) 0.0 );
    res->setv(1,3, (t_float) 0.0 );
    res->setv(2,1, (t_float) 0.0 );
    res->setv(2,2, adtrc/pold.get(2,1)*xold.get(2,1)+(alphaloc-1.+adtrc)*uold.get(1,1) );
    res->setv(2,3, adtrc/pold.get(3,1)*(xold.get(2,1)+pold.get(2,1)*uold.get(1,1)) ) ;

	return Nx*Np;
}

t_size	CellModel_R0R1C1::CoercePars( Vector * const pp )
{
	t_size cntCoerce = 0;
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: CoercePars( Vector * const pp )" );
#endif

	if( pp->get(1,1) <= (t_float) 0.0 ) {
	      pp->setv(1,1, CellModel::CellModel::Zero );
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_COERCE )
	      dbg_print( "WARNING: parameter p(1,1)=R0<=0 CORRECTED TO ZERO" );
#endif
	      cntCoerce++;
	}

	if( pp->get(2,1) < (t_float) 0.0 ) {
	      pp->setv(2,1, CellModel::CellModel::Zero );
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_COERCE )
	      dbg_print( "WARNING: parameter p(2,1)=R1<=0 CORRECTED TO ZERO" );
#endif
	      cntCoerce++;
	}

	if( pp->get(3,1) < (t_float) 0.0 )
	{
	      pp->setv(3,1, CellModel::Zero );
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_COERCE )
	      dbg_print( "WARNING: parameter p(3,1)=C1<0 CORRECTED TO ZERO" );
#endif
	      cntCoerce++;
	}

	return cntCoerce;
}

t_size	CellModel_R0R1C1::CoerceState( Vector * const xx )
{
	t_size cntCoerce = 0;
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: CoerceState( Vector * const xx )" );
#endif

	if( xx->get(1,1) > (t_float) 1 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_COERCE )
	    dbg_print( "WARNING: state x(1,1)=SOC>1. CORRECTED TO 1" );
#endif
	    cntCoerce++;
	} else if( xx->get(1,1) < (t_float) 0.0 ) {
		xx->setv(1,1, 1);
#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_COERCE )
	    dbg_print( "WARNING: state x(1,1)=SOC<0. CORRECTED TO ZERO" );
#endif
	    cntCoerce++;
	}

    return cntCoerce;
}

#if _ARCHITECTURE_ == ARCH_PC || DBGCHK_CELL_MODEL( DBGMSK_CELL_MODEL_INFO )
t_size CellModel_R0R1C1::Info( char * strCellModel )
{
	/* AUTO genereted Class Member */
	char strThisModel[] = "R0R1C1";

#if DBGCHK_R0R1C1( DBGMSK_R0R1C1_CLASS )
    CellModel_R0R1C1_dprint( "CALL: Info( char * strCellModel )" );
#endif

    strcpy( strCellModel, strThisModel );
	return (t_size) strlen( strThisModel );
}
#endif // ARCH_PC || DBGMSK_CELL_MODEL_INFO 
