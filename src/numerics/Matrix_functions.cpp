/*
 * Matrix_functions.cpp
 *
 *  Created on: 18/nov/2014
 *      Author: delloiaconos
 */


#include <beast/numerics/Matrix.h>
#include <beast/numerics/Vector.h>

/* Locally used functions */
void Swap(t_float& a, t_float& b);
void Swap(t_float* a, t_float* b);

void Swap(t_float& a, t_float& b)
{
	register t_float temp = a;
	a = b;
	b = temp;
}

void Swap(t_float* a, t_float* b)
{
	register t_float temp = *a;
	*a = *b;
	*b = temp;
}


/*
 * i.e. for i=1 the function returns the number of rows,
 * and for i=2 the function returns the number of columns
 * else the function returns 0
 */
t_size Size(const Matrix& a, const t_size i)
{
	return a.Size(i);
}


/**
 * returns a matrix with size cols x rows with ones as values
 */
Matrix Ones(const t_size rows, const t_size cols)
{
	Matrix res = Matrix(rows, cols);

	for (t_size r = 1; r <= rows; r++)
	{
		for (t_size c = 1; c <= cols; c++)
		{
			res(r, c) = 1;
		}
	}
	return res;
}

/**
 * returns a matrix with size cols x rows with zeros as values
 */
Matrix Zeros(const t_size rows, const t_size cols)
{
	return Matrix(rows, cols);
}


/**
 * returns a diagonal matrix with size n x n with ones at the diagonal
 * @param  v a vector
 * @return a diagonal matrix with ones on the diagonal
 */
Matrix Diag(const t_size n)
{
	Matrix res = Matrix(n, n);
	for (t_size i = 1; i <= n; i++)
	{
		res(i, i) = 1;
	}
	return res;
}

/**
 * returns a diagonal matrix
 * @param  v a vector
 * @return a diagonal matrix with the given vector v on the diagonal
 */
Matrix Diag(const Matrix& v)
{
	Matrix res;
	if (v.GetCols() == 1)
	{
		// the given matrix is a vector n x 1
		t_size rows = v.GetRows();
		res = Matrix(rows, rows);

		// copy the values of the vector to the matrix
		for (t_size r=1; r <= rows; r++)
		{
			res(r, r) = v.get(r, 1);
		}
	}
	else if (v.GetRows() == 1)
	{
		// the given matrix is a vector 1 x n
		t_size cols = v.GetCols();
		res = Matrix(cols, cols);

		// copy the values of the vector to the matrix
		for (t_size c=1; c <= cols; c++)
		{
			res(c, c) = v.get(1, c);
		}
	}
	else
	{
		throw Exception("Parameter for diag must be a vector");
	}
	return res;
}

/*
 * returns the determinant of Matrix a
 */
t_float Det(const Matrix& a)
{
	t_float d = 0;    // value of the determinant
	t_size rows = a.GetRows();
	t_size cols = a.GetRows();

	if (rows == cols)
	{
		// this is a square matrix
		if (rows == 1)
		{
			// this is a 1 x 1 matrix
			d = a.get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 matrix
			// the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
			d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
		}
		else
		{
			// this is a matrix of 3 x 3 or larger
			for (t_size c = 1; c <= cols; c++)
			{
				Matrix M = a.Minor(1, c);
				//d += pow(-1, 1+c) * a(1, c) * Det(M);
				d += (c%2 + c%2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
			}
		}
	}
	else
	{
		throw Exception("Matrix must be square");
	}
	return d;
}



/*
 * returns the inverse of Matrix a
 */
Matrix Inv(const Matrix& a)
{
	Matrix res;
	t_float d = 0;    // value of the determinant
	t_size rows = a.GetRows();
	t_size cols = a.GetRows();

	d = Det(a);
	if (rows == cols && d != 0)
	{
		// this is a square matrix
		if (rows == 1)
		{
			// this is a 1 x 1 matrix
			res = Matrix(rows, cols);
			res(1, 1) = 1 / a.get(1, 1);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 matrix
			res = Matrix(rows, cols);
			res(1, 1) = a.get(2, 2);
			res(1, 2) = -a.get(1, 2);
			res(2, 1) = -a.get(2, 1);
			res(2, 2) = a.get(1, 1);
			res = (1/d) * res;
		}
		else
		{
			// this is a matrix of 3 x 3 or larger
			// calculate inverse using gauss-jordan elimination
			//   http://mathworld.wolfram.com/MatrixInverse.html
			//   http://math.uww.edu/~mcfarlat/inverse.htm
			res = Diag(rows);   // a diagonal matrix with ones at the diagonal
			Matrix ai = a;    // make a copy of Matrix a

			for (t_size c = 1; c <= cols; c++)
			{
				// element (c, c) should be non zero. if not, swap content
				// of lower rows
				t_size r;
				for (r = c; r <= rows && ai(r, c) == 0; r++)
				{
				}
				if (r != c)
				{
					// swap rows
					for (t_size s = 1; s <= cols; s++)
					{
						Swap(ai(c, s), ai(r, s));
						Swap(res(c, s), res(r, s));
					}
				}

				// eliminate non-zero values on the other rows at column c
				for (t_size r = 1; r <= rows; r++)
				{
					if(r != c)
					{
						// eleminate value at column c and row r
						if (ai(r, c) != 0)
						{
							t_float f = - ai(r, c) / ai(c, c);

							// add (f * row c) to row r to eleminate the value
							// at column c
							for (t_size s = 1; s <= cols; s++)
							{
								ai(r, s) += f * ai(c, s);
								res(r, s) += f * res(c, s);
							}
						}
					}
					else
					{
						// make value at (c, c) one,
						// divide each value on row r with the value at ai(c,c)
						t_float f = ai(c, c);
						for (t_size s = 1; s <= cols; s++)
						{
							ai(r, s) /= f;
							res(r, s) /= f;
						}
					}
				}
			}
		}
	}
	else
	{
		if (rows == cols)
		{
			throw Exception("Matrix must be square");
		}
		else
		{
			throw Exception("Determinant of matrix is zero");
		}
	}
	return res;
}
