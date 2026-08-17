/*
 * gaussj.h
 *
 *  Created on: 04/dic/2014
 *      Author: delloiaconos
 */

#ifndef __GAUSSJ_H__
#define __GAUSSJ_H__

#include <beast/common/commons.h>

#define GAUSSJ_MATRIXCHECK TRUE

t_size gaussj_AxB( Matrix& aa, Matrix& bb );
t_size gaussj_xAB( Matrix& aa, Matrix& bb );

#endif // __GAUSSJ_H__
