// header part.

#ifndef GRADITO_H_
#define GRADITO_H_

#include <stddef.h>
#include <stdio.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

// defining matrix struct.
// very light structure. just contains 3 values of 64 bits, the structure itself doesnt contain the data.
typedef struct {
    size_t rows; // size_t is 64  bits.
    size_t cols;
    float *es; // pointer to the beginning of the data.
} Matrix;

// SAFEKEEPER MACRO OF PRINTING THE MATRIX.
// when we printing the matrix we have to take the row and we have to skip i rows. and the size of the rows is amount of columns.
// the variables must be in () just because of expressions like i+1.
#define MATRIX_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

// dynamic memory.
Matrix mat_alloc(size_t rows, size_t cols);
void matrix_rand(Matrix m, float low, float high);
void matrix_dot(Matrix dst, Matrix a, Matrix b);
void matrix_sum(Matrix dst, Matrix a);
void matrix_print(Matrix m, const char *id);
void matrix_fill(Matrix m, float z);

#endif // GRADITO_H_

// C part.

#ifdef GRADITO_IMPLEMENTATION

// return a random number from 0 to 1.
float rand_float(void){
    return (float) rand() / (float) RAND_MAX;
}

Matrix mat_alloc(size_t rows, size_t cols){
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.es = NN_MALLOC(sizeof(*m.es)*rows*cols); // allocate memory. *m.es in case that we want to change de datatype to other one.
    NN_ASSERT(m.es != NULL); // check if pointer is null.
    return m;
}

// defining dotproduct matrix operation.
// output matrix first just for convention.
// if we have matrix A(4x2) and matrix B(2x5). then matrix DST(4x5).
void matrix_dot(Matrix dst, Matrix a, Matrix b){
  NN_ASSERT(a.cols == b.rows); // to do matrix multiplication, the columns of the first matrix needs to have the same dimention that the rows of the second matrix.
  NN_ASSERT(dst.rows == a.rows);
  NN_ASSERT(dst.cols == b.cols);

  size_t n = a.cols; // interstice.

  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j = 0; j < dst.cols; ++j){
      MATRIX_AT(dst, i, j) = 0;
      for(size_t k = 0; k < n; ++k){
        MATRIX_AT(dst, i, j) += MATRIX_AT(a, i, k) * MATRIX_AT(b, k, j); // i and j are used to go through the rows and cols. but k its the variable that is used to do the operation. 
      }
    }
  }
}

// defining sum matrix operation.
void matrix_sum(Matrix dst, Matrix a){
  NN_ASSERT(dst.rows == a.rows); // to add two matrices, they need to have the same # of rows and cols.
  NN_ASSERT(dst.cols == a.cols);

  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j = 0; j < dst.cols; ++j){
      MATRIX_AT(dst, i, j) += MATRIX_AT(a, i, j);
    }
  }
}

// printing the matrix on screen. id is the name of the matrix.
void matrix_print(Matrix m, const char *id){
  printf("%s = [\n", id);
  for(size_t i = 0; i < m.rows; ++i){
    for(size_t j = 0; j < m.cols; ++j){
      printf("   %f ", MATRIX_AT(m, i, j)); // with the macro we avoid later issues.
      }
      printf("\n");
  }
  printf("]\n");
}

// randomize the values.
void matrix_rand(Matrix m, float low, float high){
  for(size_t i = 0; i < m.rows; ++i){
    for(size_t j = 0; j < m.cols; ++j){
      MATRIX_AT(m, i, j) = rand_float()*(high - low) + low;
      }
    printf("\n");
  }
}

void matrix_fill(Matrix m, float z){
  for(size_t i = 0; i < m.rows; ++i){
    for (size_t j = 0; j < m.cols; ++j) {
      MATRIX_AT(m, i, j) = z;
      }
  }
}
#endif //GRADITO_IMPLEMENTATION
