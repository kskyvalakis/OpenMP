/*

The is the third attempt to a parralel pi program.  This time to avoid
false sharing we use a critical section.

*/

#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2

static long num_steps = 100000000;
double step;

int main ()
{
	  double start_time, run_time, pi;
		step = 1.0/(double) num_steps;
		omp_set_num_threads(NUM_THREADS);

	  start_time = omp_get_wtime();
		#pragma omp parallel
		{
			int i, id, nthrds;
			double x,sum;
			id = omp_get_thread_num();
			nthrds = omp_get_num_threads();

			for (i=id, sum=0.0; i<num_steps; i=i+nthrds)
			{
				x = (i+0.5)*step;
				sum += 4.0/(1.0+x*x);
			}
			#pragma omp critical
				pi += sum*step;
			//instead of #pragma omp critical code block
			//we could use the following code block with the exact same outcome
			//sum = sum*step;
			//#pragma atomic
			//pi += sum;

		}

	  run_time = omp_get_wtime() - start_time;
		printf("Result: %f\n",pi);
	  printf("Time: %f seconds",run_time);
}
