//approximately calculate pi
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>


static long num_steps = 100000;
double step;

//number of threads in the team


int main() {
	int nthreads = 4;
	omp_set_num_threads(nthreads);
	#pragma omp parallel
	
		
	{
		int i;
		double x, pi, sum = 0.0;
		//thread Id or rank
		int ID = omp_get_thread_num();
		double start = omp_get_wtime();
		step = 1.0 / (double)num_steps;
		for (i = 0; i < num_steps; i++) {
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x);
		}
		pi = step * sum;
		double end = omp_get_wtime();
		double duration = end - start;
		printf("\n pi with %ld steps is %lf in %d seconds\n ", num_steps, pi, ID);
		printf("with %d thread:\n", omp_get_num_threads());
		printf("The duration of work is:%f\n", duration);
		printf("All done with hopefully %d threads: \n", nthreads);
	}




}