#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float or_w1;
    float or_w2;
    float or_b;
    
    float nand_w1;
    float nand_w2;
    float nand_b;
    
    float and_w1;
    float and_w2;
    float and_b;    
} Xor;

float sigmoidf(float x){
    return 1.f / (1.f + expf(-x)); // expf works with floats
}

float forward(Xor m, float x1, float x2) {

    float a = sigmoidf(m.or_w1*x1 + m.or_w2*x2 + m.or_b);
    float b = sigmoidf(m.nand_w1*x1 + m.nand_w2*x2 + m.nand_b);

    return sigmoidf(a*m.and_w1 + b*m.and_w2 + m.and_b);
}

// XOR gate
float train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float loss(Xor m){
	float result = 0.0f;
	for (size_t i = 0; i < train_count; ++i) {
		float x1 = train[i][0];
        float x2 = train[i][1];
		float y = forward(m, x1, x2);
		float dist = y - train[i][2];
		result += dist*dist;
	}
	result /= train_count;
	return result;
}

float rand_float(void)
{
	return (float) rand() / (float) RAND_MAX;
}

Xor rand_xor(void) {
    Xor m;
    m.and_w1 = rand_float()*0.2f;
    m.and_w2 = rand_float()*0.2f;
    m.and_b = rand_float()*0.2f;
    m.or_w1 = rand_float()*0.2f;
    m.or_w2 = rand_float()*0.2f;
    m.or_b = rand_float()*0.2f;
    m.nand_w1 = rand_float()*0.2f;
    m.nand_w2 = rand_float()*0.2f;
    m.nand_b = rand_float()*0.2f;
    
    return m;
}

void print_xor(Xor m) {
    printf("and_w1: %f\n", m.and_w1);
    printf("and_w2: %f\n", m.and_w2);
    printf("and_b: %f\n", m.and_b);
    printf("or_w1: %f\n", m.or_w1);
    printf("or_w2: %f\n", m.or_w2);
    printf("or_b: %f\n", m.or_b);
    printf("nand_w1: %f\n", m.nand_w1);
    printf("nand_w2: %f\n", m.nand_w2);
    printf("nand_b: %f\n", m.nand_b); 
}

Xor diff_operation(Xor m, Xor grad, float l_rate) {
    m.and_w1 -= l_rate*grad.and_w1;
    m.and_w2 -= l_rate*grad.and_w2;
    m.and_b -= l_rate*grad.and_b;
    m.or_w1 -= l_rate*grad.or_w1;
    m.or_w2 -= l_rate*grad.or_w2;
    m.or_b -= l_rate*grad.or_b;
    m.nand_w1 -= l_rate*grad.nand_w1;
    m.nand_w2 -= l_rate*grad.nand_w2;
    m.nand_b -= l_rate*grad.nand_b;

    return m;  
}

Xor finite_difference(Xor m, float eps) {
    float l = loss(m);
    Xor grad;
    float saved_w;

    saved_w = m.and_w1;
    m.and_w1 += eps;
    grad.and_w1 = (loss(m) - l) / eps;
    m.and_w1 = saved_w;

    saved_w = m.and_w2;
    m.and_w2 += eps;
    grad.and_w2 = (loss(m) - l) / eps;
    m.and_w2 = saved_w;

    saved_w = m.and_b;
    m.and_b += eps;
    grad.and_b = (loss(m) - l) / eps;
    m.and_b = saved_w;

    saved_w = m.or_w1;   
    m.or_w1 += eps;
    grad.or_w1 = (loss(m) - l) / eps;
    m.or_w1 = saved_w;

    saved_w = m.or_w2;
    m.or_w2 += eps;
    grad.or_w2 = (loss(m) - l) / eps;
    m.or_w2 = saved_w;

    saved_w = m.or_b;
    m.or_b += eps;
    grad.or_b = (loss(m) - l) / eps;
    m.or_b = saved_w;

    saved_w = m.nand_w1;
    m.nand_w1 += eps;
    grad.nand_w1 = (loss(m) - l) / eps;
    m.nand_w1 = saved_w;

    saved_w = m.nand_w2;
    m.nand_w2 += eps;
    grad.nand_w2 = (loss(m) - l) / eps;
    m.nand_w2 = saved_w;

    saved_w = m.nand_b;
    m.nand_b += eps;
    grad.nand_b = (loss(m) - l) / eps;
    m.nand_b = saved_w;

    return grad;
}

int main(void) {
    srand(time(0));
    Xor m = rand_xor();
    float eps = 1e-1;
    float l_rate = 0.02;
    
    for(size_t i = 0; i < 500000; ++i){
        Xor grad = finite_difference(m, eps);
        m = diff_operation(m, grad, l_rate);
        printf("loss: %f\n", loss(m));
    }

    for(size_t i = 0; i < 2; ++i){
        for(size_t j = 0; j < 2; ++j){
            printf("%zu ^ %zu = %f\n", i, j, forward(m, i, j));
        }
    }
    return 0;
}