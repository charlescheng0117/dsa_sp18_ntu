#include <iostream>
#include <vector>
#include <fstream>
#include <limits>


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

void display(vector< vector<double> >& mat) {
	int n = mat.size();

	// i : row, j : col
	for (int i = 0; i < n; i += 1) {
		int col = mat[i].size();
		for (int j = 0; j < col; j += 1) {
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void extend(vector< vector<double> >& mat) {  
	/* Set the right half of mat to an identity matrix
	   for Gaussian elimination. 
	   Only works for square matrix.
	*/

	int n = mat.size(); // rows

	for (int row = 0; row < n; row += 1 ) {
		mat[row][row + n] = 1;
	}

	return;
}

void row_exchange(vector< vector<double> >& mat, entry& source, entry& target) {
	/* Deal with the zero row problem. */
	int row_sc = source.row, col_sc = source.col;
	int row_tg = target.row, col_tg = target.col;

	int ncol = mat[row_sc].size();
	double tmp;

	for (int i = 0; i < ncol; i += 1) {
		tmp = mat[row_tg][i];
		mat[row_tg][i] = mat[row_sc][i];
		mat[row_sc][i] = tmp;
	}
}

void row_op_mul(vector< vector<double> >& mat, int row, double cof) {
	/* Multiply the whole row with cof. */
	int n = mat[0].size(); // n columns
	for (int i = 0; i < n; i += 1) {
		mat[row][i] *= cof;
	}
	return;
}

void row_op_add(vector< vector<double> >& mat, entry& source, entry& target) {
	/* add row `from' to row `to' */
	int row_sc = source.row, col_sc = source.col;
	int row_tg = target.row, col_tg = target.col;

	//printf("row_sc = %d col_sc = %d\n", row_sc, col_sc);
	//printf("row_tg = %d col_tg = %d\n", row_tg, col_tg);

	int ncol = mat[row_sc].size();

	if (mat[row_sc][col_sc] == 0) {
		// should just do row exchange here.
		row_exchange(mat, source, target);
		return;
	}

	double cof = - (mat[row_tg][col_tg] / mat[row_sc][col_sc]) ;
	//cout << cof << '\n';

	for (int i = 0; i < ncol; i += 1 ) {
		mat[row_tg][i] += cof * mat[row_sc][i];
	}
	return;
}

vector< vector<double> > inv(vector< vector<double> >& mat) {
	/* find inv using gaussian elmination.
	   start from col = 0, 1, ..., n - 1
	   dim of mat 		 = n x  n
	   dim of mat_extend = n x 2n

	   return inv(mat)
	*/

	int n = mat.size();

	vector< vector<double> > mat_extend(n, vector<double> (2 * n) );

	// copy the content of mat to mat_ex
	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			mat_extend[i][j] = mat[i][j];
		}
	}

	extend(mat_extend);

	/* make mat a U. */
	for (int col = 0; col < n; col += 1) {
		entry from(col, col);
		for (int row = col + 1; row < n; row += 1) {
			entry to(row, col);
			row_op_add(mat_extend, from, to);
		}
	}

	/* make mat a L. */
	for (int col = n - 1; col > -1; col -= 1) {
		entry from(col, col);
		for (int row = col - 1; row > -1; row -= 1) {
			entry to(row, col);
			row_op_add(mat_extend, from, to);
		}
	}

	/* normalized the pivot entry to 1. */
	for (int i = 0; i < n; i += 1) {
		double cof = 1 / mat_extend[i][i];
		row_op_mul(mat_extend, i, cof);
	}

	//display(mat_extend);

	vector< vector<double> > inv_mat(n, vector<double> (n) );

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			inv_mat[i][j] = mat_extend[i][n + j];
		}
	}

	return inv_mat;
}

vector< vector<double> > transpose(vector< vector<double> >& mat) {
	int m = mat.size(), n = mat[0].size();
	vector< vector<double> > ret(n, vector<double> (m));

	for (int i = 0; i < m; i += 1) {
		for (int j = 0; j < n; j += 1) {
			ret[j][i] = mat[i][j];
		}
	}
	return ret;
}

double dot(vector<double>& v1, vector<double>& v2) {
	int n1 = 0, n2 = 0;
	double ret = 0.0;
	if ( (n1 = v1.size() ) != (n2 = v2.size() ) ){
		printf("dim of v1 = %d, dim of v2 = %d\n", n1, n2);
		return -1;
	}

	for (int i = 0; i < n1; i += 1 ) {
		ret = ret + (v1[i] * v2[i]);
	}

	return ret;
}

vector< vector<double> > dot(vector< vector<double> >& mat1, vector< vector<double> >& mat2) {
	/* Dimension of mat1 = m x n
	   Dimension of mat2 = n x k
	*/
	int m = mat1.size(), n = mat2.size(), k = mat2[0].size();
	vector< vector<double> > ret(m, vector<double> (k) );

	if (mat1[0].size() != n) {
		printf("mat1: %d x %lu, mat2: %d x %d, Dim is not right.\n", m, mat1[0].size(), n, k);
		return ret;
	}

	// since we get the element of mat1 `` row by row '',
	// we first transpose mat2 to get its element `` column by column ''
	// then we can calculate the entry of ret easily.
	vector< vector<double> > mat2_tr = transpose(mat2);


	for (int i = 0; i < m; i += 1) {
		for (int j = 0; j < k; j += 1) {
			ret[i][j] = dot(mat1[i], mat2_tr[j]);
		}
	}

	return ret;
}

double calc_err(vector< vector<double> >& A, vector< vector<double> >& B) {
	double ret = - numeric_limits<double>::infinity();
	int n = A.size();
	vector< vector<double> > AB_minus_I = dot(A, B);

	for (int i = 0; i < n; i += 1) {
		AB_minus_I[i][i] -= 1.0;
	}

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			if (AB_minus_I[i][j] > ret)
				ret = AB_minus_I[i][j];
		}
	}

	return ret;

}

void test_003(vector< vector<double> >& mat) {
	mat[0][0] = 1, mat[0][1] = 1, mat[0][2] = 1;
	mat[1][0] = 1, mat[1][1] = 2, mat[1][2] = 3;
	mat[2][0] = 1, mat[2][1] = 3, mat[2][2] = 6;
	return;
}

void test_op() {
	int n = 3;
	vector< vector<double> > mat_003_ex(n, vector<double> (2 * n) );
	/* add op. */

	test_003(mat_003_ex);
	display(mat_003_ex);

	/* extended form of mat_003 */
	extend(mat_003_ex);
	display(mat_003_ex);
	cout << "add op.\n";
	entry from(0, 0), to(1, 0);
	row_op_add(mat_003_ex, from, to);
	display(mat_003_ex);

	to.row = 2;
	row_op_add(mat_003_ex, from, to);
	display(mat_003_ex);

	/* row_exchange */
	row_op_add(mat_003_ex, to, from);
	display(mat_003_ex);
}

void test_dot() {
	vector< vector<double> > B { {3, 4, 5, 2},
								 {5, 3, 2, 1},
								 {1, 7, 3, 1} },
							 mat_003 { {1, 1, 1},
							 		   {1, 2, 3},
							 		   {1, 3, 6} }, inv_003, B_T, B_T_B, I;
							 
	display(B);

	B_T = transpose(B);
	display(B_T);

	vector<double> v1 {1, 2, 3}, v2 {3, 4, 5}, v3 {0, 1};

	// test for inner product
	double inner = dot(v1, v2);
	cout << "inner is " << inner << "\n";

	// test for error
	dot(v1, v3);

	// test for BTB
	B_T_B = dot(B_T, B);
	display(B_T_B);

	inv_003 = inv(mat_003);

	cout << "Start testing!\n";
	I = dot(mat_003, inv_003);
	display(I);
	cout << calc_err(mat_003, inv_003) << "\n";

}

int main(int argc, char **argv) {
	/* for redirect */
	
	if (argc != 3) {
		cout << "Usage: ./yourprogram input ouput\n";
		return 1;
	}

	char *infile = argv[1];
	char *outfile = argv[2];

	fstream ifs;
	fstream ofs;

	ifs.open(infile, fstream::in);
	if (!ifs.is_open()) 
		cout << "Can't open " <<  infile << "\n";

	ofs.open(outfile, fstream::out);
	if (!ifs.is_open()) 
		cout << "Can't open " <<  infile << "\n";

	int n;
	ifs >> n;

	vector< vector<double> > A(n, vector<double> (n) );
	//vector< vector<double> > A_ex(n, vector<double> (2 * n) );

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			ifs >> A[i][j];
			//A_ex[i][j] = A[i][j];
		}
	}

	vector< vector<double> > B = inv(A), I;
	//display(B);

	I = dot(A, B);

	printf("I =\n");
	display(I);

	double err = 0.0;
	ofs << calc_err(A, B) << "\n";

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n; j += 1) {
			ofs << B[i][j] << " ";
		}
		ofs << "\n";
	}

	ifs.close();
	ofs.close();
	

	//test_dot();

	return 0;
}