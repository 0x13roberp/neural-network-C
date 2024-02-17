#define GRADITO_IMPLEMENTATION
#include "gradito.h"

int main(void){
    Matrix m = mat_alloc(1, 4); // defining a matrix of 4x4
    matrix_rand(m, 0, 10);
    matrix_print(m);
    return 0;
}
