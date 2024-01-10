#define NN_IMPLEMENTATION
#include "nn.h"

int main(void){
    Matrix m = mat_alloc(4, 4);
    matrix_rand(m, 0, 10);
    matrix_print(m);
    return 0;
}