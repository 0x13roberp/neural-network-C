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
float loss(float w){
	float result = 0.0f;
	for (size_t i = 0; i < train_count; ++i) {
		float x = train[i][0];
		float y = x*w;
		float dist = y - train[i][1];
		result += dist*dist; // mse
	}
	result /= train_count;
	return result;
}

int main()
{
	// srand(time(0)); // initialize random numbers
	srand(69);
	float w = rand_float()*10.0f;
	float eps = 1e-3;
	float l_rate = 1e-3 ;
	
	// finite difference, not derivative
	printf("%f\n", loss(w));
	float derivative = (loss(w + eps) - loss(w))/eps;
	w -= l_rate*derivative;
	printf("%f\n", loss(w));

	return 0;
}
