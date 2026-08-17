/* 
 * Class: CellModel_R0A1B1
 * Created by Salvatore Dello Iacono Gio 17-Apr-2014 10:34
 *
 */
#include <beast/cell_models/CellModel_R0A1B1.h>

#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>
#include <beast/numerics/interpolation.h>

#if _ARCHITECTURE_ == ARCH_PC
	#include <string.h>
#endif


CellModel_R0A1B1::CellModel_R0A1B1()
{
#if R0A1B1_DBG( DBG_R0A1B1_ENB )
   CellModel_DebugInit();
#endif
   
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
   dbg_print( "CALL: CellModel_R0A1B1::CellModel_R0A1B1()" );
#endif   
   Nx = 2;
   Np = 3;
   Nu = 1;
   Ny = 1;

   sxW = Matrix( Matrix::Identity, Nx, Nx);
   sxV = Matrix( Matrix::Identity, Ny, Ny);
   spR = Matrix( Matrix::Identity, Np, Np);
   spE = Matrix( Matrix::Identity, Ny, Ny);

/* Initialize */
#if _ARCHITECTURE_ != ARCH_PC
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

#endif // _ARCHITECTURE_ != ARCH_PC

}

#if _ARCHITECTURE_ == ARCH_PC
CellModel_R0A1B1::CellModel_R0A1B1( char * basepath )
{
	FILE * fr;
	char filename[2*CELL_MODEL_BASEPATH_LEN];

#if R0A1B1_DBG( DBG_R0A1B1_ENB )
   CellModel_DebugInit();
#endif

#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
   dbg_print( "CALL: CellModel_R0A1B1::CellModel_R0A1B1(char * basepath )" );
#endif

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

   /* Read from file */
   do {
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
   } while(0);

   do {
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
   } while(0);

   do {
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

   } while(0);

   do {
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

     } while(0);


   do {
	   // Qn_Ah
  	   t_float tmpQn;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_pfix_Qn_Ah.in" );
  	   fr = fopen( filename, "r" );
  	   fread( &tmpQn, sizeof(t_float), (t_size) 1, fr );
  	   Qnom = tmpQn*3600;
  	   fclose( fr );
     } while(0);

   do {
	   // eta
  	   t_float tmpEta;
  	   strcpy( filename, basepath );
  	   strcat( filename, "/MD_pfix_eta.in" );
  	   fr = fopen( filename, "r" );
  	   fread( &tmpEta, sizeof(t_float), (t_size) 1, fr );
  	   eta = tmpEta;
  	   fclose( fr );
     } while(0);

   do {
   // lut_soc; lutlen
	   t_float tmp;
	   strcpy( filename, basepath );
	   strcat( filename, "/MD_pfix_soc.in" );
	   fr = fopen( filename, "r" );
	   lutlen = 0;
	   while( !feof(fr) && lutlen < R0A1B1_LUT_MAXLEN )
	   {
		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
		   lutsoc[lutlen] = tmp;
		   lutlen++;
	   }
	   fclose( fr );
   	  } while(0);

   do {
	   t_float tmp;
	   t_size i;
	   strcpy( filename, basepath );
	   strcat( filename, "/MD_pfix_ocv0.in" );
	   fr = fopen( filename, "r" );

	   for( i = 0; ( i < lutlen ) && !feof(fr); i++ )
	   {
		   fread( &tmp, sizeof(t_float), (t_size) 1, fr );
		   lutocv0[i] = tmp;
	   }

	   fclose( fr );
   } while(0);

   do {
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
      } while(0);
}
#endif


#if R0A1B1_DBG( DBG_R0A1B1_ENB )
void inline CellModel_R0A1B1::CellModel_DebugInit( void )
{    
   fdbg = fopen( "CellModel_R0A1B1_dbg.txt", "wt" );

#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
   dbg_print( "CALL: CellModel_R0A1B1::CellModel_DebugInit()" );
#endif
}
#endif


CellModel_R0A1B1::~CellModel_R0A1B1()
{
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
   dbg_print( "CALL: CellModel_R0A1B1::~CellModel_R0A1B1()" );
#endif

#if R0A1B1_DBG( DBG_R0A1B1_ENB )
    fclose( fdbg );
#endif 
}

t_size CellModel_R0A1B1::f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res )
{
	t_float deltaSOC;
	t_float u;
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::f0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res )" );
#endif

    u = (t_float) uold.get(1,1);
    CoulombCountingConstant = deltat / Qnom;

    deltaSOC = CoulombCountingConstant*u;
    res->setv(1,1, xold.get(1,1)-deltaSOC );
    res->setv(2,1, pold.get(2,1)*xold.get(2,1)+pold.get(3,1)*u );

    return Nx;
}


t_size CellModel_R0A1B1::g0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res )
{   
	t_float ocv0old;
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::y0( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const ynew )" );
#endif
    ocv0old = interpxy( lutsoc, lutocv0, lutlen, xold.get( 1, 1 ) );

    res->setv(1,1, ocv0old - pold.get(1,1)*uold.get(1,1)+xold.get(2,1));
    return Nu;
}


t_size CellModel_R0A1B1::f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::f1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif
    res->setv(1,1, 1);
    res->setv(1,2, 0);
    res->setv(2,1, 0);
    res->setv(2,2, pold.get(2,1) );

    return Nx*Np;
}


t_size CellModel_R0A1B1::f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::f1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    res->setv(1,1, 0);
    res->setv(1,2, 0);
    res->setv(1,3, 0);
    res->setv(2,1, 0);
    res->setv(2,2, xold.get(2,1) );
    res->setv(2,3, uold.get(1,1) );

	return Nx*Np;
}


t_size CellModel_R0A1B1::g1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )
{
	t_float ocv1old;

#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::y1x( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif
    ocv1old = interpxy( lutsoc, lutocv1, lutlen, xold.get( 1, 1 ) );

    res->setv(1,1, ocv1old );
    res->setv(1,2, 1);

    return Nu*Nx;
}



t_size CellModel_R0A1B1::g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Vector * const res )
{
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
    dbg_print( "CALL: CellModel_R0A1B1::g1p( const Vector &xold, const Vector &pold, const Vector &uold, t_float deltat, Matrix * const res )" );
#endif

    res->setv(1,1, -uold.get(1,1) );
    res->setv(1,2, 0);
    res->setv(1,3, 0);

    return Nu*Np;
}

t_size	CellModel_R0A1B1::CoercePars( Vector * const pp )
{
	t_size cnt = 0;
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
	      dbg_print( "CALL: CellModel_R0A1B1::CoercePars( Vector * const pp )" );
#endif

	if( pp->get(1,1) <= (t_float) 0.0 ) {
	      pp->setv(1,1, CellModel::CellModel::Zero );
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	      dbg_print( "WARNING: parameter p(1,1)=R0<=0 CORRECTED TO ZERO" );
#endif
	      cnt++;
	}

	if( pp->get(2,1) < (t_float) 0.0 ) {
	      pp->setv(2,1, CellModel::CellModel::Zero );
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	      dbg_print( "WARNING: parameter p(2,1)=A1<=0 CORRECTED TO ZERO" );
#endif
	      cnt++;
	} else if( pp->get(2,1) > (t_float) 1.0) {
	      pp->setv(2,1, 1 );
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	      dbg_print( "WARNING: parameter p(2,1)=A1<1 CORRECTED TO 1" );
#endif
	      cnt++;
	}

	if( pp->get(3,1) > (t_float) 0.0 )
	{
	      pp->setv(3,1, -CellModel::Zero );
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	      dbg_print( "WARNING: parameter p(3,1)=B1>=0 CORRECTED TO -ZERO" );
#endif
	      cnt++;
	}

	return cnt;
}

t_size	CellModel_R0A1B1::CoerceState( Vector * const xx )
{
	t_size cnt = 0;
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
	dbg_print( "CALL: CellModel_R0A1B1::CoerceState( Vector * const xx )" );
#endif

	if( xx->get(1,1) > (t_float) 1 ) {
		xx->setv(1,1, 1);
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	    dbg_print( "WARNING: state x(1,1)=SOC>1. CORRECTED TO 1" );
#endif
	    cnt++;
	} else if( xx->get(1,1) < (t_float) 0.0 ) {
		xx->setv(1,1, 1);
#if R0A1B1_DBG( DBG_R0A1B1_COERCE )
	    dbg_print( "WARNING: state x(1,1)=SOC<0. CORRECTED TO ZERO" );
#endif
	    cnt++;
	}

	return cnt;
}


#ifdef DBG_CELL_MODEL_INFO
t_size CellModel_R0A1B1::CellModel_Info( char * strCellModel )
{
#if R0A1B1_DBG( DBG_R0A1B1_CLASS )
	dbg_print( "CALL: CellModel_R0A1B1::CellModel_Info( char * strCellModel )" );
#endif
	char strThisModel[] = "R0A1B1";

	return (t_size) strcpy( strCellModel, strThisModel );;
}
#endif // DBG_CELL_MODEL_INFO
