#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// activation func
float sigmoidf(float x){
    return 1.f / (1.f + expf(-x)); // expf works with floats
}

// NAND gate
float train[][3] = {
    {0, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float loss(float w1, float w2, float b){
	float result = 0.0f;
	for (size_t i = 0; i < train_count; ++i) {
		float x1 = train[i][0];
        float x2 = train[i][1];
		float y = sigmoidf(x1*w1 + x2*w2 + b);
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

int main(void) {
    srand(time(0));
    float eps = 1e-1;
    float l_rate = 1e-1;
    float b = rand_float();
    float w1 = rand_float();
    float w2 = rand_float();
    
    for(size_t i = 0; i < 50000; ++i)
    {
        float l = loss(w1, w2, b);
        float dw1 = (loss(w1 + eps, w2, b) - l)/eps;
        float dw2 = (loss(w1, w2 + eps, b) - l)/eps;
        float db = (loss(w1, w2, b + eps) - l)/eps;
        w1 -= l_rate*dw1;
        w2 -= l_rate*dw2;
        b -= l_rate*db;

        //printf("w1: %f, w2: %f, b: %f, loss: %f\n", w1, w2, b, l);
    }

    for(size_t i = 0; i < 2; ++i){
        for(size_t j = 0; j < 2; ++j){
            printf("%zu | %zu = %f\n", i, j, sigmoidf(i*w1 + j*w2 + b));
        }
    }
    return 0;
}