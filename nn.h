#ifndef NN_H_
#define NN_H_

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

typedef struct {
    size_t rows;
    size_t cols;
    float *es;

} Matrix;

#define MATRIX_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

float rand_float(void);

Matrix mat_alloc(size_t rows, size_t cols);
void matrix_rand(Matrix m, float low, float high);
void matrix_dot(Matrix dst, Matrix a, Matrix b);
void matrix_sum(Matrix dst, Matrix a);
void matrix_print(Matrix m);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION
float rand_float(void){
    return (float) rand() / (float) RAND_MAX;
}
Matrix mat_alloc(size_t rows, size_t cols){
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.es = NN_MALLOC(sizeof(*m.es)*rows*cols);
    NN_ASSERT(m.es != NULL);
    return m;
}
void matrix_dot(Matrix dst, Matrix a, Matrix b){
    (void) dst;
    (void) a;
    (void) b;
}

void matrix_sum(Matrix dst, Matrix a){
    (void) dst;
    (void) a;
}

void matrix_print(Matrix m){
    for(size_t i = 0; i < m.rows; ++i){
        for(size_t j = 0; j < m.cols; ++j){
            printf("%f ", MATRIX_AT(m, i, j));
        }
        printf("\n");
    }
    (void) m;
}

void matrix_rand(Matrix m, float low, float high){
    for(size_t i = 0; i < m.rows; ++i){
        for(size_t j = 0; j < m.cols; ++j){
            MATRIX_AT(m, i, j) = rand_float()*(high - low) + low;
        }
        printf("\n");
    }
}
#endif //NN_IMPLEMENTATION