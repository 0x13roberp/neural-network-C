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

float rand_float(void);

// dynamic memory.
Matrix mat_alloc(size_t rows, size_t cols);
void matrix_rand(Matrix m, float low, float high);
void matrix_dot(Matrix dst, Matrix a, Matrix b);
void matrix_sum(Matrix dst, Matrix a);
void matrix_print(Matrix m);

#endif // GRADITO_H_

// C part.

#ifdef GRADITO_IMPLEMENTATION
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
void matrix_dot(Matrix dst, Matrix a, Matrix b){
    (void) dst;
    (void) a;
    (void) b;
}

// defining sum matrix operation
void matrix_sum(Matrix dst, Matrix a){
    (void) dst;
    (void) a;
}

// printing the matrix on screen
void matrix_print(Matrix m){
    for(size_t i = 0; i < m.rows; ++i){
        for(size_t j = 0; j < m.cols; ++j){
            printf("%f ", MATRIX_AT(m, i, j)); // with the macro we avoid later issues.
        }
        printf("\n");
    }
    (void) m;
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
#endif //GRADITO_IMPLEMENTATION
