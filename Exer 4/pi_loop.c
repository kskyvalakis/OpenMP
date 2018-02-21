#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;

int main ()
{
	int i;
	double start_time, run_time, x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;

	start_time = omp_get_wtime();
	#pragma omp parallel
	{
		double x;
		#pragma omp for reduction(+:sum)
		for (i=0; i<num_steps; i++)
		{
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	}

	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("Result: %f\n",pi);
	printf("Time: %f seconds",run_time);
}
