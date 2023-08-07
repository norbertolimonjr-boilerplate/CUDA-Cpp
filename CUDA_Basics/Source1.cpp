#include<iostream>
#include<math.h>


__global__
void add(int n, float* x, float* y) {
	for (int i = 0; i < n; i++)
		y[i] = x[i] + y[i];
}

int main(void) {
	int N = 1 << 20; //1M elements
	/*
	float* a = new float[N];
	float* b = new float[N];
	*/
	float* a, * b;
	cudaMallocManaged(&a, N * sizeof(float));
	cudaMallocmanaged(&b, N * sizeof(float));

	// initialize x and y arrays on the host
	for (int i = 0; i < N; i++) {
		a[i] = 1.0f;
		b[i] = 2.0f;
	}

	// Run the kernel on 1M elements using the CPU
	add(N, a, b);

	// Check for errors (all values should be 3.0f)
	float maxError = 0.0f;
	for (int i = 0; i < N; i++)
		maxError = fmax(maxError, fabs(b[i] - 3.0f));
	std::cout << "Max error: " << maxError << std::endl;

	// Free allocated memory
	/*
	delete[] a;
	delete[] b;
	*/
	cudaFree(a);
	cudaFree(b);

	return 0;
}