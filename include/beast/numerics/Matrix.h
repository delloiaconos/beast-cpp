#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <beast/common/architecture.h>
#include <beast/common/Exception.h>

#if _ARCHITECTURE_ == ARCH_PC
	#define MATRIX_ENB_PRINT
#else
	#ifdef MATRIX_ENB_PRINT
		#undef MATRIX_ENB_PRINT
	#endif
#endif//_ARCHITECTURE_ == ARCH_PC

#ifdef MATRIX_ENB_PRINT
	#include <stdio.h>
	#include <stdlib.h>
#endif

#include <math.h>


class Matrix
{
public:
  // constructor
  Matrix();

  // constructor
  Matrix(const t_size row_count, const t_size column_count);
  Matrix(const short type, const t_size row_count, const t_size column_count);
  
  // assignment operator
  Matrix(const Matrix& a);

  // index operator. You can use this class like myMatrix(col, row)
  // the indexes are one-based, not zero based.
  t_float& operator()(const t_size r, const t_size c);

  // index operator. You can use this class like myMatrix.get(col, row)
  // the indexes are one-based, not zero based.
  // use this function get if you want to read from a const Matrix
  t_float get(const t_size r, const t_size c) const;
  
  void setv(const t_size r, const t_size c, t_float v);
  // assignment operator
  Matrix& operator= (const Matrix& a);

  // add a t_float value (elements wise)
  Matrix& Add(const t_float v);

  // subtract a t_float value (elements wise)
  Matrix& Subtract(const t_float v);
  
  // multiply a t_float value (elements wise)
  Matrix& Multiply(const t_float v);
  
  // divide a t_float value (elements wise)
  Matrix& Divide(const t_float v);

#ifdef MATRIX_ENB_PRINT
  t_size mwrite( FILE * fw );
  t_size mread( FILE * fw );
#endif

  void Transpose();
  
friend Matrix operator+(const Matrix& a, const Matrix& b)
  {
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
      Matrix res(a.rows, a.cols);

      for (t_size r = 0; r < a.rows; r++)
      {
        for (t_size c = 0; c < a.cols; c++)
        {
          res.p[r][c] = a.p[r][c] + b.p[r][c];
        }
      }
      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
  }

  // addition of Matrix with t_float
  friend Matrix operator+ (const Matrix& a, const t_float b)
  {
    Matrix res = a;
    res.Add(b);
    return res;
  }
  // addition of t_float with Matrix
  friend Matrix operator+ (const t_float b, const Matrix& a)
  {
    Matrix res = a;
    res.Add(b);
    return res;
  }

  // subtraction of Matrix with Matrix
  friend Matrix operator- (const Matrix& a, const Matrix& b)
  {
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
      Matrix res(a.rows, a.cols);

      for (t_size r = 0; r < a.rows; r++)
      {
        for (t_size c = 0; c < a.cols; c++)
        {
          res.p[r][c] = a.p[r][c] - b.p[r][c];
        }
      }
      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
  }

  // subtraction of Matrix with t_float
  friend Matrix operator- (const Matrix& a, const t_float b)
  {
    Matrix res = a;
    res.Subtract(b);
    return res;
  }
  // subtraction of t_float with Matrix
  friend Matrix operator- (const t_float b, const Matrix& a)
  {
    Matrix res = -a;
    res.Add(b);
    return res;
  }

  // operator unary minus
  friend Matrix operator- (const Matrix& a)
  {
    Matrix res(a.rows, a.cols);

    for (t_size r = 0; r < a.rows; r++)
    {
      for (t_size c = 0; c < a.cols; c++)
      {
        res.p[r][c] = -a.p[r][c];
      }
    }

    return res;
  }

  // operator multiplication
  friend Matrix operator* (const Matrix& a, const Matrix& b)
  {
    // check if the dimensions match
    if (a.cols == b.rows)
    {
      Matrix res(a.rows, b.cols);

      for (t_size r = 0; r < a.rows; r++)
      {
        for (t_size c_res = 0; c_res < b.cols; c_res++)
        {
          for (t_size c = 0; c < a.cols; c++)
          {
            res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
          }
        }
      }
      return res;
    }
    else
    {
      // give an error
      throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
  }

  // multiplication of Matrix with t_float
  friend Matrix operator* (const Matrix& a, const t_float b)
  {
    Matrix res = a;
    res.Multiply(b);
    return res;
  }
  // multiplication of t_float with Matrix
  friend Matrix operator* (const t_float b, const Matrix& a)
  {
    Matrix res = a;
    res.Multiply(b);
    return res;
  }

  // division of Matrix with t_float
  friend Matrix operator/ (const Matrix& a, const t_float b)
  {
    Matrix res = a;
    res.Divide(b);
    return res;
  }

  /**
   * returns the minor from the given matrix where
   * the selected row and column are removed
   */
  Matrix Minor(const t_size row, const t_size col) const;
  
  /*
   * returns the size of the i-th dimension of the matrix.
   * i.e. for i=1 the function returns the number of rows,
   * and for i=2 the function returns the number of columns
   * else the function returns 0
   */
  t_size Size(const t_size i) const;
  t_size Resize( const t_size newR, const t_size newC );

  // returns the number of rows
  t_size GetRows() const;

  // returns the number of columns
  t_size GetCols() const;

  // print the contents of the matrix
#ifdef MATRIX_ENB_PRINT
  void Print( FILE * fw ) const;
  void Print() const;
#endif

  void Dispose();
  
public:
  // destructor
  ~Matrix();
  static const t_size MAX_SIZE   = 4;
  static const short Identity   = 1;
  static const short Zeros      = 2;
  static const short Ones       = 3;
private:
  t_size rows;
  t_size cols;
  t_float** p;
};

// Declarations
t_float Det(const Matrix& a);
Matrix Diag(const t_size n);
Matrix Diag(const Matrix& v);
Matrix Inv(const Matrix& a);
Matrix Ones(const t_size rows, const t_size cols);
t_size Size(const Matrix& a, const t_size i);
Matrix Zeros(const t_size rows, const t_size cols);

#endif // __MATRIX_H__
