/*
 * Modified by SDI 2014-04-24
 * Created by Salvatore Dello Iacono 2014-04-24
 */

#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__



#include <beast/common/architecture.h>



#ifdef __cplusplus
extern "C" {
#endif

t_float interp1( t_float * vect, t_uint n, t_float x );
t_float interpxy( t_float * vX, t_float * vY, t_uint n, t_float x );
#ifdef __cplusplus
}
#endif // extern "C"

#endif //__INTERPOLATION_H__
