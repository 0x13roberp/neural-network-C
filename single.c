#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// we model y = x*w; where x it's the input, and w it's the weight

float train[][2] = {
	{0, 0},
	{1, 2},
	{2, 4},
	{3, 6},
	{4, 8},
};
#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void)
{
	return (float) rand() / (float) RAND_MAX;
}

// loss function
float loss(float w, float b){
	float result = 0.0f;
	for (size_t i = 0; i < train_count; ++i) {
		float x = train[i][0];
		float y = x*w+b;
		float dist = y - train[i][1];
		result += dist*dist; // mse
	}
	result /= train_count;
	return result;
}

int main()
{
	srand(time(0)); // initialize random numbers
	float w = rand_float()*10.0f;
	float b = rand_float()*2.0f;
	float eps = 1e-3;
	float l_rate = 1e-3 ;
	
	// finite difference, not derivative
	printf("%f\n", loss(w, b));
	for(size_t i = 0; i < 600; ++i)
	{
		float c = loss(w, b);
		float derivw = (loss(w + eps, b) - c)/eps;
		float derivb = (loss(w, b + eps) - c)/eps;
		w -= l_rate*derivw;
		b -= l_rate*derivb;
		printf("loss: %f\n", loss(w, b));
	}
	printf("neuron prediction: %f, bias: %f\n", w, b);
	printf("real value: %f\n", train[1][2]);
	return 0;
}
