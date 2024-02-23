#include <time.h>

#define GRADITO_IMPLEMENTATION
#include "gradito.h"

typedef struct{
  Matrix x;
  Matrix w1, b1, a1;
  Matrix w2, b2, a2;
} Xor;

void forward(Xor m){
  
  // sigmoidf(x*w1 + b).
  matrix_dot(m.a1, m.x, m.w1);
  matrix_sum(m.a1, m.b1);
  matrix_sigmoid(m.a1);

  matrix_dot(m.a2, m.a1, m.w2); // remember the fist param its the destination value.
  matrix_sum(m.a2, m.b2);
  matrix_sigmoid(m.a2);
}

Xor xor_alloc(void){
  Xor m;

  // mat alloc allocates in the first matrix (x), a 1x2 space, and so on.
  m.x = mat_alloc(1, 2); // input matrix.
  m.w1 = mat_alloc(2,2); // weights.
  m.b1 = mat_alloc(1, 2); // biases.
  m.w2 = mat_alloc(2, 1);
  m.b2 = mat_alloc(1 ,1);  
  m.a1 = mat_alloc(1, 2); // activation layers.
  m.a2 = mat_alloc(1 ,1);

  return m;
}

// function to apply "gradient descent" to all the values of the matrices.
void gradient_step(Xor m, Xor gradient, float learning_rate){

  for(size_t i = 0; i < m.w1.rows; ++i){
    for(size_t j = 0; j < m.w1.cols; ++j){
      MATRIX_AT(m.w1, i, j) -= learning_rate*MATRIX_AT(gradient.w1, i, j);
    }
  }
  for(size_t i = 0; i < m.b1.rows; ++i){
    for(size_t j = 0; j < m.b1.cols; ++j){
      MATRIX_AT(m.b1, i, j) -= learning_rate*MATRIX_AT(gradient.b1, i, j);
    }
  }
  for(size_t i = 0; i < m.w2.rows; ++i){
    for(size_t j = 0; j < m.w2.cols; ++j){
      MATRIX_AT(m.w2, i, j) -= learning_rate*MATRIX_AT(gradient.w2, i, j);
    }
  }
  for(size_t i = 0; i < m.b2.rows; ++i){
    for(size_t j = 0; j < m.b2.cols; ++j){
      MATRIX_AT(m.b2, i, j) -= learning_rate*MATRIX_AT(gradient.b2, i, j);
    }
  }
}

float loss(Xor m, Matrix train, Matrix output){
  float l = 0; // loss

  assert(train.rows == output.rows);
  assert(output.cols == m.a2.cols);
  size_t n = train.rows;

  for(size_t i = 0; i < n; ++i){
    Matrix X = matrix_row(train, i);
    Matrix y = matrix_row(output, i);

    matrix_copy(m.x, X);
    forward(m);

    for(size_t j = 0; j < output.cols; ++j){
      float difference = MATRIX_AT(m.a2, 0, j) - MATRIX_AT(y, 0, j);
      l += difference*difference;
    }
  }
  return l/n;
}

// "derivative function".
void finite_difference(Xor m, Xor gradient, Matrix train, Matrix output, float epsilon){
  float saved;
  float l = loss(m, train, output);

  for(size_t i = 0; i < m.w1.rows; ++i){
    for(size_t j = 0; j < m.w1.cols; ++j){
      saved = MATRIX_AT(m.w1, i, j); // save current values.

      MATRIX_AT(m.w1, i, j) += epsilon; // upgrade values.

      MATRIX_AT(gradient.w1, i, j) = (loss(m, train, output) - l) / epsilon; // formula.

      MATRIX_AT(m.w1, i, j) = saved; // restore the original value
    }
  }
    for(size_t i = 0; i < m.b1.rows; ++i){
      for(size_t j = 0; j < m.b1.cols; ++j){
        saved = MATRIX_AT(m.b1, i, j); 
        MATRIX_AT(m.b1, i, j) += epsilon; 
        MATRIX_AT(gradient.b1, i, j) = (loss(m, train, output) - l) / epsilon; 
        MATRIX_AT(m.b1, i, j) = saved; 
    }
  }
    for(size_t i = 0; i < m.w2.rows; ++i){
      for(size_t j = 0; j < m.w2.cols; ++j){
        saved = MATRIX_AT(m.w2, i, j); 
        MATRIX_AT(m.w2, i, j) += epsilon; 
        MATRIX_AT(gradient.w2, i, j) = (loss(m, train, output) - l) / epsilon; 
        MATRIX_AT(m.w2, i, j) = saved; 
    }
  }
    for(size_t i = 0; i < m.b2.rows; ++i){
      for(size_t j = 0; j < m.b2.cols; ++j){
        saved = MATRIX_AT(m.b2, i, j); 
        MATRIX_AT(m.b2, i, j) += epsilon; 
        MATRIX_AT(gradient.b2, i, j) = (loss(m, train, output) - l) / epsilon; 
        MATRIX_AT(m.b2, i, j) = saved; 
    }
  }
}

float training_data[] = {
  0, 0, 0,
  0, 1, 1,
  1, 0, 1,
  1, 1, 0,
};

int main(void){
  srand(time(0));

  size_t stride = 3;
  size_t n = sizeof(training_data) / sizeof(training_data[0]) / stride;
  Matrix train = {
    .rows = n,
    .cols = 2,
    .stride = stride,
    .es = training_data
  };

  Matrix output = {
    .rows = n,
    .cols = 1,
    .stride = stride,
    .es = training_data + 2,
  };

  Xor m = xor_alloc();
  Xor gradient = xor_alloc();

  float epsilon = 1e-1;
  float learning_rate = 1e-1;

  // the activations matrices doesnt need to be randomized.
  matrix_rand(m.w1, 0, 1); 
  matrix_rand(m.b1, 0, 1); 
  matrix_rand(m.w2, 0, 1); 
  matrix_rand(m.b2, 0, 1);

  // print the matrices with their respective name.
  matrix_print(train, "train");
  matrix_print(output, "output");

  printf("first loss: %f\n", loss(m, train, output));

  for(size_t i = 0; i < 100*100; ++i){
    finite_difference(m, gradient, train, output, epsilon); // apply the "derivative".
    gradient_step(m, gradient, learning_rate); // apply the "gradient descent".
  
    printf("loss: %f\n", loss(m, train, output));
  }
  // truth table.
  for(size_t i = 0; i < 2; ++i){
    for(size_t j = 0; j < 2; ++j){
      MATRIX_AT(m.x, 0, 0) = i;
      MATRIX_AT(m.x, 0, 1) = j;
      forward(m);
      float y = *m.a2.es;

      printf("%zu ^ %zu = %f\n", i, j, y);
    }
  }
  return 0;
}
