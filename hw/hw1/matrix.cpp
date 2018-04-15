#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

using namespace std;

struct entry {
public:
	entry(int i, int j) {
		row = i;
		col = j;
	}
   
	int row;
	int col;
};

void row_exchange(Matrix& mat, int from, int to) { // perform row exchange operation
	/* Deal with the zero row problem. */
	int ncol = mat.col;
	double tmp;

	for (int i = 0; i < ncol; i += 1) {
		tmp = mat.array[to][i];
		mat.array[to][i] = mat.array[from][i];
		mat.array[from][i] = tmp;
	}
}

void row_op_mul(Matrix& mat, int row, double cof) {
	/* Multiply the whole row with cof. */
	int ncol = mat.col; // n columns
	for (int i = 0; i < ncol; i += 1) {
		mat.array[row][i] *= cof;
	}
	return;
}

void row_elimination(Matrix& mat, entry& source, entry& target) {
	/* perform gaussian elimination from entry `source' to `target' */
	int row_sc = source.row, col_sc = source.col;
	int row_tg = target.row, col_tg = target.col;
	int ncol = mat.col;

	if (mat.array[row_sc][col_sc] == 0) {
		// should just do row exchange here.
		row_exchange(mat, row_sc, row_tg);
		return;
	}

	double cof = - (mat.array[row_tg][col_tg] / mat.array[row_sc][col_sc]) ;

	for (int i = 0; i < ncol; i += 1 ) {
		mat.array[row_tg][i] += cof * mat.array[row_sc][i];
	}
	return;
}

Matrix extend(const Matrix& mat) {  
	/* Creat a matrix with dim: n x 2n where
	   right half of mat to an identity matrix
	   for Gaussian elimination. 
	   Only works for square matrix.
	*/

	int ncol = mat.col;
	Matrix ret(ncol, 2 * ncol);



	for (int i = 0; i < ncol; i += 1 ) {
		ret.array[i][i + ncol] = 1;
		for (int j = 0; j < ncol; j += 1 ) {
			ret.array[i][j] = mat.array[i][j];
		}
	}

	return ret;
}

Matrix::Matrix(const int& r, const int& c) //constructor
{
	row = r;
	col = c;
	array = new double*[r];
	for (int i = 0; i < r; ++i) {
		array[i] = new double[c];
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			array[i][j] = 0.0;
		}
	}
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	row = rhs.row;
	col = rhs.col;

	array = new double*[row];
	for (int i = 0; i < row; ++i) {
		array[i] = new double[col];
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			array[i][j] = rhs.array[i][j];
		}
	}
}

Matrix::~Matrix() //destructor
{
	for (int i = 0; i < row; ++i) {
		delete [] array[i];
	}
	delete [] array;
}

double* & Matrix::operator [](const int& idx) const	// Enable the use of A[i][j] instead of A.array[i][j]
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment operator
{
	if (this != &rhs) {
		
		for (int i = 0; i < row; ++i) {
			delete [] array[i];
		}
		delete [] array;

		row = rhs.row;
		col = rhs.col;

		array = new double*[row];
		for (int i = 0; i < row; ++i ) {
			array[i] = new double[col];
			for (int j = 0; j < col; ++j) {
				array[i][j] = rhs.array[i][j];
			}
		}
		
	} 

	/* BUG  BUG  BUG  BUG  BUG  BUG  BUG  BUG
	Matrix tmp(rhs);
	return tmp;
	*/
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix ret(*this);
	for (int i = 0; i < row; ++i ) {
		for (int j = 0; j < col; ++j ) {
			ret.array[i][j] = - ret.array[i][j]; 
		}
	}
	return ret;
}

Matrix Matrix::operator +() const
{
	Matrix ret(*this);
	return ret;
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix ret(*this);
	for (int i = 0; i < row; ++i ) {
		for (int j = 0; j < col; ++j ) {
			ret.array[i][j] = ret.array[i][j] - rhs.array[i][j]; 
		}
	}
	return ret;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
	Matrix ret(*this);
	for (int i = 0; i < row; ++i ) {
		for (int j = 0; j < col; ++j ) {
			ret.array[i][j] = ret.array[i][j] + rhs.array[i][j]; 
		}
	}
	return ret;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
	// Assume the dimension is compatible
	int ret_row = row;
	int ret_col = rhs.col;
	int rhs_row = rhs.row;

	Matrix ret(ret_row, ret_col);

	for (int i = 0; i < ret_row; i += 1) {
		for (int j = 0; j < ret_col; j += 1) {
			double tmp = 0.0;
			for (int k = 0; k < rhs_row; k += 1) {
				tmp = tmp + (array[i][k] * rhs.array[k][j]);
			}
			ret.array[i][j] = tmp;
		}
	}

	return ret;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{	
	Matrix inv_rhs = rhs.inverse();

	return (*this) * inv_rhs;
}

Matrix Matrix::inverse() const
{
	/* find inv using gaussian elmination.
	   start from col = 0, 1, ..., n - 1
	   dim of mat 		 = n x  n
	   dim of mat_extend = n x 2n
	*/

	int n = col;

	Matrix mat_ext = extend(*this);

	/* make mat a U. */
	for (int col = 0; col < n; col += 1) {
		entry from(col, col);
		for (int row = col + 1; row < n; row += 1) {
			entry to(row, col);
			row_elimination(mat_ext, from, to);
		}
	}

	/* make mat a L. */
	for (int col = n - 1; col > -1; col -= 1) {
		entry from(col, col);
		for (int row = col - 1; row > -1; row -= 1) {
			entry to(row, col);
			row_elimination(mat_ext, from, to);
		}
	}

	/* normalized the pivot entry to 1. */
	for (int i = 0; i < n; i += 1) {
		double cof = 1 / mat_ext[i][i];
		row_op_mul(mat_ext, i, cof);
	}

	Matrix inv_mat(n, n);

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			inv_mat.array[i][j] = mat_ext.array[i][n + j];
		}
	}

	return inv_mat;
}

void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if(fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if(fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
	fclose(fp);
}

void Matrix::print() const
{
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			printf("%lf%c", array[i][j], " \n"[j==col-1]);
}
