#include <iostream>
#include <immintrin.h>
#include <chrono>
#include <conio.h>
#include <math.h>
/* A generic function for allocating aligned memory for any alignment
Calcuating the address of first aligned byte:
Example: alignment = 32, base address was 325
=> 325 + 32 - (325 % 32)
=> 357 - 5
=> 352*/
void *malloc_aligned_generic(size_t alignment, size_t size)
{
	char *p1;
	p1 = (char *)malloc(size + alignment + sizeof(void *));
	p1 += sizeof(void *);
	void *p2 = (void *)((uintptr_t)p1 + alignment - ((uintptr_t)p1 % alignment));
	*((void **)((uintptr_t)p2 - sizeof(void *))) = p1 - sizeof(void *);
	return p2;
}

void free_aligned(void *memory) {
	void *p = *((void **)((uintptr_t)memory - sizeof(void *)));
	free(p);
}

void cosx(int N, int terms, float* x, float* result)
{
	for (int i = 0; i<N; i++)
	{
		float value = 1;
		float numer = x[i] * x[i] ;
		int denom = 2; //2!
		int sign = -1;
		for (int j = 1; j <= terms; j++)
		{
			value += sign * numer / denom;
			numer *= x[i] * x[i] * x[i] * x[i];
			denom *= (2 * j + 2) * (2 * j + 1); sign *= -1;
		}
		result[i] = value;
	}
}

void cosx_avx(unsigned long long N, unsigned short terms, float x[], float result[])
{
	for (int i = 0; i < N; i += 8)
	{
		__m256 origx = _mm256_load_ps(&x[i]);
		__m256 value = origx;
		__m256 numer = _mm256_mul_ps(origx, _mm256_mul_ps(origx, origx));
		__m256 denom = _mm256_set1_ps(6);
		float sign = -1;
		for (int j = 1; j <= terms; j++)
		{
			__m256 tmp = _mm256_div_ps(_mm256_mul_ps(_mm256_set1_ps(sign), numer), denom);
			value = _mm256_add_ps(value, tmp);
			numer = _mm256_mul_ps(numer, _mm256_mul_ps(origx, origx));
			denom = _mm256_mul_ps(denom, _mm256_set1_ps((2 * (float)j + 2) * (2 * (float)j + 3)));
			sign *= -1;
		}
		_mm256_store_ps(&result[i], value);
	}
}

int main()
{
	const unsigned long long N = (unsigned long long) (8 * 10e6);
	const unsigned short NUM_TERMS = 7;
	float *result;
	float *x;
	result = (float *)malloc_aligned_generic(32, sizeof(float)* N);
	x = (float *)malloc_aligned_generic(32, sizeof(float)* N);
	for (int i = 0; i < N; ++i)
		x[i] = 1;
	long t1 = clock();
	sinx_avx(N, NUM_TERMS, x, result);
	printf("\r\nTime using AVX = %d ms\r\n", clock() - t1);
	t1 = clock();
	cosx(N, NUM_TERMS, x, result);
	printf("\r\nTime using normal code = %d ms\r\n", clock() - t1);
	printf(" x= %f,", x[5]);
	printf("calculated cosine = %f ,", result[5]);
	printf("real cosine = %f ,", cos(1));
	free_aligned(x);
	free_aligned(result);
	getche;
	
	return 0;
}