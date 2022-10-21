//approximately calculate pi
/*
The idea is I have a single program and I run multiple copies of that program.
Each thread has its own copy.

We define nthreads, nthrds, and all related parameter inside of parallel region,
then they will sit on stack for each thread. Outside the parallel region we lost 
all parameters. So, if I defined sum inside of parallel region, I cannot access 
it outside of parallel region, so sum should be shared. So, NUM_THREADS is a global 
variable and sum and all defined parameters before e#pragma omp parallel are shared variables.

*/
#include<omp.h>
#include<stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 2

int main() {

	int i, nthreads;
	double pi, sum[NUM_THREADS];
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	
	{
		int i, nthrds;
		double x;
		//thread Id or rank
		int ID = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		double start = omp_get_wtime();
		//this line is for master thread, to force inside of parallel region
		//to use the exact defined number of threads, because MPI by default 
		//would like to assign as less as possible thread
		if (ID == 0) nthreads = nthrds;
		for (i = ID; sum[ID] < num_steps; i = i + nthrds) {
			x = (i + 0.5) * step;
			sum[ID] = sum[ID] + 4.0 / (1.0 + x * x);
		}
	}
	for (i = 0, pi = 0.0; i < nthreads; i++) {
		pi = step * sum[i];
	}
	printf("\n pi with %ld steps is %lf\n ", num_steps, pi);
	//printf("with %d thread:\n", nthrds);
		
	printf("All done with hopefully %d threads: \n", nthreads);
	
}