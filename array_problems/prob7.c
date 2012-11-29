#include <stdio.h>
#include <stdlib.h>

/* Problem 7
 *   Write an algorithm such that if an element in an MxN matrix is 0, its entire row
 *   and column is set to 0.
 */

// To solve this problem, all there is to be done is search for zeros BUT not modify
// the matrix at the first pass -- otherwise, all elements would become zero.
// So, we do a two pass in the matrix. In the first pass, we mark all the rows and
// columns that have zeros. The second pass, we change the matrix, 'zeroing' the
// correct rows and columns.

// Function to print the matrix, helps debugging
void printMatrix(int** matrix, int M, int N) {
  int i, j;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}

// Searches for 0's in a given row. If a row has a 0 as one of its elements, then
// zero_row[row_number] is marked as 'zeroable'. At the same time, it marks the
// zero_col[column] position of the zero in the row, making that column of the
// original matrix 'zeroable'.
void searchRow(int* row, int row_number, int N, int* zero_row, int* zero_col) {
  int i;

  // If a zero is found, then we mark that row as 'zeroable' and mark the column
  // as 'zeroable' as well.
  for (i = 0; i < N; i++) {
    if (row[i] == 0) {
      zero_row[row_number] = 1;
      zero_col[i] = 1;
    }
  }
}

// Modifies matrix based on rows and columns marked as 'zeroable'
void modifyMatrix(int** matrix, int M, int N, int* rows, int* cols) {
  int i, j;

  // Check each row if there is a zero. If there is, modify all elements in that row.
  for (i = 0; i < M; i++) {
    if (rows[i] == 1) {
      for (j = 0; j < N; j++) {
	matrix[i][j] = 0;
      }
    }
  }

  // Do the same procedure, but now in the columns. If an element in a column is
  // zero, then we need to modify all elements in that particular column.
  for (i = 0; i < N; i++) {
    if (cols[i] == 1) {
      for (j = 0; j < M; j++) {
	matrix[j][i] = 0;
      }
    }
  }
}

// This function will verify if a matrix has 0's and will modify it accordingly.
// To verify that the matrix has 0's as one (or more) of its elements, the function
// will pass each row to the searchRow() function, which will do a search for 0's
// that are stored in that particular row.
void setZeros(int** matrix, int M, int N) {
  int* columns;
  int* rows;
  int i, j;

  // allocates memory for arrays rows and columns, which will keep track of zeros
  // for the rows and columns of the matrix. We do not have to make another matrix
  // to do this calculation. This way, instead of doing it in O(MN) space required
  // by another matrix, we do it in O(M+N) space.
  rows = (int*) calloc(N, sizeof(int) * M);
  columns = (int*) calloc(N, sizeof(int) * N);

  // search for 0's in each row of the matrix
  for (i = 0; i < M; i++) {
    searchRow(matrix[i], i, N, rows, columns); 
  }

  // print initial matrix (debug)
  printMatrix(matrix, M, N);

  // modify matrix according to the presence of 0's
  modifyMatrix(matrix, M, N, rows, columns);

  // print result (debug)
  printMatrix(matrix, M, N);
}

// Testing...
int main() {
  int M;
  int N;
  int i, j;
  int count = 1;
  int** matrix;

  M = 3;
  N = 4;

  // seed
  srand((unsigned) time(NULL));

  // Allocate matrix
  matrix = (int**) malloc(sizeof(int*) * M);

  for (i = 0; i < M; i++) {
    matrix[i] = (int*) malloc(sizeof(int) * N);
  }

  // Populate matrix
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      matrix[i][j] = rand() % (M + N);
    }
  }

  // Set Zeros
  setZeros(matrix, M, N);

  // Free pointers
  for (i = 0; i < M; i++) {
    free(matrix[i]);
  }

  free(matrix);

  return 0;
}
