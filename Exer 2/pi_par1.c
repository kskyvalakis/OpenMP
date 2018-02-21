/*

The is the first attempt to a parralel pi program.  Though it introduces false
sharing and to solve it we will use padding to our sum array. See pi_par2.c .

*/

#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2

static long num_steps = 100000000;
double step;

int main ()
{
	  int i, nthreads;
	  double start_time, run_time, pi, sum[NUM_THREADS];
		step = 1.0/(double) num_steps;
		omp_set_num_threads(NUM_THREADS);

	  start_time = omp_get_wtime();
		#pragma omp parallel
		{
			int i, id, nthrds;
			double x;
			id = omp_get_thread_num();
			nthrds = omp_get_num_threads();
			if(id==0) nthreads = nthrds;
			//i could use id==0 or id==1 it doesnt matter
			//i do it to make sure that, in case the system doesnt give me
			//the requested number of threads, i know how many it gave me

			for (i=id, sum[id]=0.0; i<num_steps; i=i+nthrds)
			{
				x = (i+0.5)*step;
				sum[id] += 4.0/(1.0+x*x);
			}
		}

	  for(i=0, pi=0.0; i<nthreads; i++) pi += sum[i]*step;

	  run_time = omp_get_wtime() - start_time;
		printf("Result: %f\n",pi);
	  printf("Time: %f seconds",run_time);
}
