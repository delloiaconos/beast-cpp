changequote(`$', `$')dnl
changecom()dnl
// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Estimator "$$BEAST_NAME$$" implementation.
 *
 * @details
 * Part of the BEAST project:
 * Battery Estimation Architecture and Simulation Toolkit.
 *
 * BEAST is a framework for battery modeling, simulation, and state/parameter
 * estimation.
 *
 * @author $$BEAST_AUTHOR$$
 * @date $$BEAST_YEAR$$
 *
 * @par Project
 * BEAST - Battery Estimation Architecture and Simulation Toolkit
 *
 * @par Repository
 * $$BEAST_REPOSITORY$$
 *
 * @copyright
 * Copyright (c) $$BEAST_YEAR$$ $$BEAST_AUTHOR$$.
 *
 * @license
 * GNU General Public License v3.0.
 */

#ifndef __ESTIMATOR_$$BEAST_UPPER_NAME$$_DEBUG_H__
#define __ESTIMATOR_$$BEAST_UPPER_NAME$$_DEBUG_H__


/* Tipi di debug disponibili */
#define DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_ENABLE        	0x80
#define DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_CLASS        	0x01
#define DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_COERCE			0x02
#define DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_STEPBYSTEP		0x04


#define DEBUG_ESTIMATOR_$$BEAST_UPPER_NAME$$       ( DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_ENB )

#define ESTIMATOR_$$BEAST_UPPER_NAME$$_DBG( dbg )      ( defined(DEBUG_ESTIMATOR_$$BEAST_UPPER_NAME$$) && \
                                             ( DEBUG_ESTIMATOR_$$BEAST_UPPER_NAME$$ & DBG_ESTIMATOR_$$BEAST_UPPER_NAME$$_ENB ) && \ 
                                             ( DEBUG_ESTIMATOR_$$BEAST_UPPER_NAME$$ & (dbg) )  )


#if ESTIMATOR_$$BEAST_UPPER_NAME$$_DBG( DBG_MIXALGORITHM_ENB )

#endif

#endif // __ESTIMATOR_$$BEAST_UPPER_NAME$$_DEBUG_H__
