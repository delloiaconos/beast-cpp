// SPDX-License-Identifier: GPL-3.0-only

/**
 * @file
 * @brief Matrix Class Implementation.
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

#include <beast/numerics/Matrix.h>

#include <stdio.h>
#include <stdlib.h>


// constructor
Matrix::Matrix()
{
	//printf("Executing constructor Matrix() ...\n");
	// create a Matrix object without content
	p = (t_float **) NULL;
	rows = 0;
	cols = 0;
}

// constructor
Matrix::Matrix(const t_size row_count, const t_size column_count)
{
	p = (t_float **) NULL;

	if (row_count > 0 && column_count > 0)
	{
		rows = row_count;
		cols = column_count;

		p = new t_float*[rows];
		for (t_size r = 0; r < rows; r++)
		{
			p[r] = new t_float[cols];
			for (t_size c = 0; c < cols; c++)
			{
				p[r][c] = 0;
			}
		}
	}
}

// constructor
Matrix::Matrix(const short type, const t_size row_count, const t_size column_count)
{
	p = (t_float **) NULL;

	if (row_count > 0 && column_count > 0)
	{
		rows = row_count;
		cols = column_count;

		p = new t_float*[rows];
		for (t_size r = 0; r < rows; r++)
		{
			p[r] = new t_float[cols];
			for (t_size c = 0; c < cols; c++)
				switch( type )
				{
				case Matrix::Identity:
					p[r][c] = r == c ? 1 : 0;
					break;
				case Matrix::Ones:
					p[r][c] = 1;
					break;
				default:
					p[r][c] = 0;
					break;
				}
		}
	}
}

// assignment operator
Matrix::Matrix(const Matrix& a)
{
	rows = a.rows;
	cols = a.cols;
	p = new t_float*[a.rows];
	for (t_size r = 0; r < a.rows; r++)
	{
		p[r] = new t_float[a.cols];

		// copy the values from the matrix a
		for (t_size c = 0; c < a.cols; c++)
		{
			p[r][c] = a.p[r][c];
		}
	}
}

// index operator. You can use this class like myMatrix(col, row)
// the indexes are one-based, not zero based.
t_float& Matrix::operator()(const t_size r, const t_size c)
{
	if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

// index operator. You can use this class like myMatrix.get(col, row)
// the indexes are one-based, not zero based.
// use this function get if you want to read from a const Matrix
t_float Matrix::get(const t_size r, const t_size c) const
{
	if (p != (t_float **) NULL && r > 0 && r <= rows && c > 0 && c <= cols)
	{
		return p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

void Matrix::setv(const t_size r, const t_size c, t_float v)
{
	if (p != (t_float **) NULL && r > 0 && r <= rows && c > 0 && c <= cols)
	{
		p[r-1][c-1] = v;
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}
// assignment operator
Matrix& Matrix::operator= (const Matrix& a)
{
	if (this == &a)
		return *this;

	for (t_size r = 0; r < rows; r++)
		delete[] p[r];
	delete[] p;

	rows = a.rows;
	cols = a.cols;
	p = rows > 0 ? new t_float*[rows] : (t_float**) NULL;
	for (t_size r = 0; r < rows; r++)
	{
		p[r] = new t_float[cols];
		for (t_size c = 0; c < cols; c++)
			p[r][c] = a.p[r][c];
	}
	return *this;
}

// add a t_float value (elements wise)
Matrix& Matrix::Add(const t_float v)
{
	for (t_size r = 0; r < rows; r++)
	{
		for (t_size c = 0; c < cols; c++)
		{
			p[r][c] += v;
		}
	}
	return *this;
}

// subtract a t_float value (elements wise)
Matrix& Matrix::Subtract(const t_float v)
{
	return Add(-v);
}

// multiply a t_float value (elements wise)
Matrix& Matrix::Multiply(const t_float v)
{
	for (t_size r = 0; r < rows; r++)
	{
		for (t_size c = 0; c < cols; c++)
		{
			p[r][c] *= v;
		}
	}
	return *this;
}

// divide a t_float value (elements wise)
Matrix& Matrix::Divide(const t_float v)
{
	return Multiply(1/v);
}

void Matrix::Transpose( void )
{
	t_size c,r;
	if( rows == cols ) {
		for( c = 0; c < cols; c++ )
			for( r = c; r < rows; r++ ) {
				t_float tmp = p[r][c];
				p[r][c] = p[c][r];
				p[c][r] = tmp;
			}
	} else {
		Matrix M = Matrix( cols, rows );

		for( c = 0; c < cols; c++ )
			for( r = 0; r < rows; r++ )
				M( c+1,r+1 ) = p[r][c];

		r = rows;
		c = cols;

		//Dispose();

		for (r = 0; r < rows; r++)
			delete[] p[r];
		delete[] p;

		cols = r;
		rows = c;

		p = new t_float*[rows];

		for (r = 0; r < rows; r++) {
			p[r] = new t_float[cols];
			for (c = 0; c < cols; c++)
				p[r][c] = M(r+1,c+1);
		}
	}
}

/**
 * returns the minor from the given matrix where
 * the selected row and column are removed
 */
Matrix Matrix::Minor(const t_size row, const t_size col) const
{
	Matrix res;
	if (row > 0 && row <= rows && col > 0 && col <= cols)
	{
		res = Matrix(rows - 1, cols - 1);

		// copy the content of the matrix to the minor, except the selected
		for (t_size r = 1; r <= (rows - (row >= rows)); r++)
		{
			for (t_size c = 1; c <= (cols - (col >= cols)); c++)
			{
				res(r - (r > row), c - (c > col)) = p[r-1][c-1];
			}
		}
	}
	else
	{
		throw Exception("Index for minor out of range");
	}

	return res;
}

/*
 * returns the size of the i-th dimension of the matrix.
 * i.e. for i=1 the function returns the number of rows,
 * and for i=2 the function returns the number of columns
 * else the function returns 0
 */
t_size Matrix::Size(const t_size i) const
{
	if (i == 1)
	{
		return rows;
	}
	else if (i == 2)
	{
		return cols;
	}
	return 0;
}

t_size Matrix::Resize( const t_size newR, const t_size newC )
{
	if (newR <= rows && newC <= cols ) {
		rows = newR;
		cols = newC;
		/* TODO: Resize
		 * 	for (t_size r = 0; r < rows; r++)
		 *		{delete p[r]; }
		 */
		return 1;
	} else {
		return 255;
	}

	return 0;
}
// returns the number of rows
t_size Matrix::GetRows() const
{
	return rows;
}

// returns the number of columns
t_size Matrix::GetCols() const
{
	return cols;
}

#ifdef MATRIX_ENB_PRINT
// print the contents of the matrix
void Matrix::Print( FILE * fw ) const
{
	if (p != (t_float **) NULL)
	{
		fprintf( fw, "[");
		for (t_size r = 0; r < rows; r++)
		{
			if (r > 0)
				fprintf( fw, " ");

			for (t_size c = 0; c < cols-1; c++)
				fprintf( fw, "%.4e, ", p[r][c]);

			fprintf( fw, "%.4e%c\n", p[r][cols-1], (r < rows-1) ? ';' : ']'  );
		}
	}
	else
	{
		fprintf( fw, "[ ]\n");
	}
}
void Matrix::Print() const { Print( stdout ); }
#endif

// destructor
Matrix::~Matrix()
{
	// clean up allocated memory
	for (t_size r = 0; r < rows; r++)
	{
		delete[] p[r];
	}
	delete[] p;
	p = (t_float **) NULL;
	rows = cols = 0;
}

void Matrix::Dispose() {
	delete this;
}

#ifdef MATRIX_ENB_PRINT
t_size Matrix::mwrite( FILE * fw )
{
	t_size cnt = (t_size) 0;
	if( fw != (FILE *) NULL )
	{
		for (t_size r = 0; r < rows; r++)
		{
			for (t_size c = 0; c < cols; c++)
			{
				cnt += (t_size) fwrite( &p[r][c], sizeof(t_float), (t_size) 1, fw );
			}
		}
	}
	return cnt;
}
#endif

#ifdef MATRIX_ENB_PRINT
t_size Matrix::mread( FILE * fr )
{
	t_size cnt = (t_size) 0;
	if( fr != (FILE *) NULL )
	{
		for (t_size r = 0; r < rows; r++)
		{
			for (t_size c = 0; c < cols; c++)
			{
				cnt += (t_size) fread( &p[r][c], sizeof(t_float), (t_size) 1, fr );
			}
		}
	}
	return cnt;
}
#endif
