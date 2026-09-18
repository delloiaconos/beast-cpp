#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

/* Linear equation solution by Gass-Jordan elimination:
 * Solve the problem: Ax = B
 *
 *  aa {nn,nn} is the input matrix at the end this will contain the inverse
 *  bb {nn,mm} is input containing the side vector and at the end will contain the solution
 */
t_size gaussj_AxB( Matrix& aa, Matrix& bb )
{
	t_uint *indxc,*indxr, *ipiv;

	t_uint ii,icol,irow,jj,kk,l,ll;
	t_float big,pivinv,temp;

	t_uint nn, mm;

	nn = (t_size) aa.Size(1);
	mm = (t_size) bb.Size(2);

#if GAUSSJ_MATRIXCHECK == TRUE
	if( nn != (t_size) aa.Size(1) )
	{
		// ERROR: aa matrix not squared
		return 255;
	}

	if( nn != bb.Size(1) )
	{
		//ERROR: bb matrix not matching aa size
		return 255;
	}
#endif //GAUSSJ_MATRIXCHECK == TRUE

	// The integer arrays ipiv, indxr, and indxc are used  for bookkeeping on the pivoting
	indxc 	= new t_uint[nn + 1]; // from 1 to nn
	indxr 	= new t_uint[nn + 1];
	ipiv 	= new t_uint[nn + 1];
	for( ii = 0; ii <= nn; ii++) {
		indxc[ii] 	= 0;
		indxr[ii] 	= 0;
		ipiv[ii] 	= 0;
	}

	// Main Loop
	for( ii = 1; ii <= nn; ii++ ) { // This is the main loop over the columns to be reduced.
	    big = 0.0;
	    for( jj = 1; jj <= nn; jj++ ) { // This is the outer loop of the search for a pivot element.
	        if ( ipiv[jj] != 1 ) {
	        	for( kk = 1; kk <= nn; kk++ ) {
	                if ( ( ipiv[kk] == 0 ) && ( abs(aa(jj,kk)) >= big ) ) {
	                    	big = abs( aa(jj,kk) );
	                        irow = jj;
	                        icol = kk;
	    			}
	        	}
	        } // end if ipiv(jj)
	    } // end for jj

		ipiv[icol] = ipiv[icol] + 1;
	    if (irow != icol) {
	        for( l = 1; l <= nn; l++ ) {
	        	// SWAP(aa(irow,l),aa(icol,l));
	            temp = aa(irow,l);
	            aa(irow,l)=aa(icol,l);
	            aa(icol,l) = temp;
	        }
	        for( l = 1; l <= mm; l++ ) {
	        	//SWAP(bb(irow,l),bb(icol,l));
	            temp = bb(irow,l);
	            bb(irow,l)=bb(icol,l);
	            bb(icol,l) = temp;
	        }
	    } // end if (irow ~= icol)

	    indxr[ii] = irow; // We are now ready to divide the pivot row by thepivot element, located at irow and icol.
	    indxc[ii] = icol;

	    if (aa(icol,icol)==0.0) {
	    	//ERROR: Singular Matrix
	    	return 255;
	    }

		pivinv = 1.0/aa(icol,icol);
	    aa(icol,icol) = 1.0;
	    for( l=1; l <= nn; l++ ) {
	    	aa(icol,l) = pivinv*aa(icol,l);
	    }
		for( l=1; l <= mm; l++ ) {
	    	bb(icol,l) = pivinv*bb(icol,l);
		}
	    for( ll = 1; ll <= nn; ll++ ) { //Next, we reduce the rows except for the pivot one, of course.
	        if ( ll != icol ) {
	            temp = aa(ll,icol);
	            aa(ll,icol)=0.0;
	            for( l=1; l <= nn; l++ ) {
	                	aa(ll,l) = aa(ll,l) - temp*aa(icol,l);
	            }
	            for( l=1; l <= mm; l++ ) {
	                	bb(ll,l) = bb(ll,l) - temp*bb(icol,l);
	            }
	        } // end if ll
	    } // end for ll

	} // for ii - Main Loop

	for( l = nn; l >= 1; l-- ) {
		if ( indxr[l] != indxc[l] ) {
	        for( kk = 1; kk <= nn; kk++ ) {
	        	// SWAP(aa(kk,indxr(l)),aa(kk,indxc(l)));
	            temp = aa( kk, indxr[l] );
	            aa(kk, indxr[l]) = aa(kk, indxc[l] );
	            aa(kk, indxc[l] ) = temp;
	        } // end - for kk
		} // end - if
	} // end - for l

	return 0;
}


/* Linear equation solution by Gass-Jordan elimination:
 * Solve the problem: xA = B
 *
 *  aa {nn,nn} is the input matrix at the end this will contain the inverse
 *  bb {mm,nn} is input containing the side vector and at the end will contain the solution
 */
t_size gaussj_xAB( Matrix& aa, Matrix& bb )
{
	t_uint *indxc,*indxr, *ipiv;

	t_uint ii,icol,irow,jj,kk,l,ll;
	t_float big,pivinv,temp;

	t_uint nn, mm;

	nn = (t_size) bb.Size(1);
	mm = (t_size) aa.Size(2);

#if GAUSSJ_MATRIXCHECK == TRUE
	if( mm != (t_size) aa.Size(1) )
	{
		// ERROR: aa matrix not squared
		return 255;
	}

	if( mm != bb.Size(2) )
	{
		//ERROR: bb matrix not matching aa size
		return 255;
	}
#endif //GAUSSJ_MATRIXCHECK == TRUE

	// The integer arrays ipiv, indxr, and indxc are used  for bookkeeping on the pivoting
	indxc 	= new t_uint[nn + 1]; // from 1 to nn
	indxr 	= new t_uint[nn + 1];
	ipiv 	= new t_uint[nn + 1];
	for( ii = 0; ii <= nn; ii++) {
		indxc[ii] 	= 0;
		indxr[ii] 	= 0;
		ipiv[ii] 	= 0;
	}

	// Main Loop
	for( ii = 1; ii <= nn; ii++ ) { // This is the main loop over the columns to be reduced.
	    big = 0.0;
	    for( jj = 1; jj <= nn; jj++ ) { // This is the outer loop of the search for a pivot element.
	        if ( ipiv[jj] != 1 ) {
	        	for( kk = 1; kk <= nn; kk++ ) {
	                if ( ( ipiv[kk] == 0 ) && ( abs(aa(kk,jj)) >= big ) ) {
	                    	big = abs( aa(kk,jj) );
	                        irow = kk;
	                        icol = jj;
	    			}
	        	}
	        } // end if ipiv(jj)
	    } // end for jj

		ipiv[icol] = ipiv[icol] + 1;
	    if (irow != icol) {
	        for( l = 1; l <= nn; l++ ) {
	            temp = aa(l, irow);
	            aa(l, irow)=aa(l, icol);
	            aa(l, icol) = temp;
	        }
	        for( l = 1; l <= mm; l++ ) {
	            temp = bb(l, irow);
	            bb(l, irow)=bb(l, icol);
	            bb(l, icol) = temp;
	        }
	    } // end if (irow != icol)

	    indxr[ii] = irow; // We are now ready to divide the pivot row by thepivot element, located at irow and icol.
	    indxc[ii] = icol;

	    if (aa(icol,icol)==0.0) {
	    	// ERROR: Singular Matrix
	    	return 255;
	    }

		pivinv = 1.0/aa(icol,icol);
	    aa(icol,icol) = 1.0;
	    for( l=1; l <= nn; l++ ) {
	    	aa(l, icol) = pivinv*aa(l, icol);
	    }
		for( l=1; l <= mm; l++ ) {
	    	bb(l, icol) = pivinv*bb(l, icol);
		}
	    for( ll = 1; ll <= nn; ll++ ) { //Next, we reduce the rows except for the pivot one, of course.
	        if ( ll != icol ) {
	            temp = aa(icol,ll);
	            aa(icol,ll)=0.0;
	            for( l=1; l <= nn; l++ ) {
	                	aa(l,ll) = aa(l,ll) - temp*aa(l,icol);
	            }
	            for( l=1; l <= mm; l++ ) {
	                	bb(l, ll) = bb(l, ll) - temp*bb(l,icol);
	            }
	        } // end if ll
	    } // end for ll

	} // for ii - Main Loop

	for( l = nn; l >= 1; l-- ) {
		if ( indxr[l] != indxc[l] ) {
	        for( kk = 1; kk <= nn; kk++ ) {
	            temp = aa( indxr[l], kk );
	            aa( indxr[l], kk) = aa( indxc[l], kk );
	            aa( indxc[l], kk ) = temp;
	        } // end - for kk
		} // end - if
	} // end - for l

	//aainv = aa;
	//xxsol = bb;

	return 0;
}

