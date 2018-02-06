#include iostream
#includemath.h
#include conio.h
#includetime.h
#includeomp.h
#includestdio.h
#include math.h
using namespace std;
double getpi(double x, double y)
{
	double h = 0;
	double pi = 0;
	for (double i = x; i = y; i = i + 0.000000001)
	{
		h = 4.0  (1.0 + (ii));
		pi = pi + (0.000000001h);

	}
	return pi;
}
int main()
{
	
	double t1 = clock();
	double pi = getpi(0, 1);
	double t2 = clock();
	double pi2=0;
	double sumpi = 0;
#pragma omp parallel num_threads(2)
	{
		double sum1 = 0; 
		int nthr = omp_get_thread_num();
		if (nthr ==0)
		{
			
			sum1= getpi(0, 0.5);
		}
		else
		{
			sum1= getpi(0.5,1);
		}
#pragma omp critical
		{
		sumpi += sum1 ;
		}
	}
	double t3 = clock();
	cout  pi  endl  t2 - t1  endl   sumpi  endl  t3 - t2;
	return 0;

}