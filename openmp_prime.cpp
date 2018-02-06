#include "stdio.h"
#include <conio.h>
#include <omp.h>
#include <math.h>
#include<iostream>
#include <time.h>
using namespace std;
#define li 10000000
bool isprime(int x)
{
	if (x == 1)
		return false;
	if ( x == 2)
		return true;
	for (int i = 2; i <= sqrt(x*1.000000); i++)
	{
		if (x%i == 0)
			return false;
		
	}
	return true;
}
int main()
{
	int counter1 = 0;
	int counter2 = 0;
	double t1 =  clock();
	for (int i = 2; i < li; i++)
	{
	
		if (isprime(i) == 1)
		{
			counter1 ++;
		
		}
	}
	double t2 = clock();
	
	cout << counter1 << endl << t2 - t1 << endl;
	
	int nofth[4]={2, 4, 8, 12};
	for (int j = 0; j <= 3; j++)
	{
		double t3 = clock();
#pragma omp parallel num_threads(nofth[j])
		{
			int nthr = omp_get_thread_num();
			double sum1 = 0;
			
			
#pragma omp parallel for schedule(static,1)
				for (int i = ((li*nthr) / nofth[j]) + 1; i < (li*(nthr + 1)) / nofth[j]; i++)
				{

					if (isprime(i) == 1)
					{
						sum1 += 1;

					}
				}
			
#pragma omp critical
			{
				counter2 += sum1;
			}
		}
		double t4 = clock();
		cout << endl <<counter2 << endl << t4-t3;
		counter2 = 0;
	}
	return 0;
	


}