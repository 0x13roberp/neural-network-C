#include <time.h>

#define GRADITO_IMPLEMENTATION
#include "gradito.h"

int main(void){
  srand(time(0));

  // mat alloc allocates in the first matrix a 2x2 space, and so on.
  Matrix w1 = mat_alloc(2,2); // weights
  Matrix b1 = mat_alloc(1, 2); // biases
  Matrix w2 = mat_alloc(2, 1);
  Matrix b2 = mat_alloc(1 ,1);

  matrix_rand(w1, 0, 1); 
  matrix_rand(b1, 0, 1); 
  matrix_rand(w2, 0, 1); 
  matrix_rand(b2, 0, 1);

  matrix_print(w1, "w1");
  matrix_print(b1, "b1");
  matrix_print(w2, "w2");
  matrix_print(b2, "b2");
  return 0;
}
