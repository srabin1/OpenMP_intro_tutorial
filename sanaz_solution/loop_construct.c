/*
Exercise 4: parallelize the serial pi program with a loop construct
*/
#include <omp.h>
#include <stdio.h>

// I can remove all ids, omp_get_num , and all functions related to SPMD
// alot easier than SPMD
static long num_steps = 100000;
double step;

int main() {
	int i;
	double x, pi, sum = 0.0;
	step = 1.0 / (double)num_steps;
	
	#pragma omp parallel
	{
		double x;
		#pragma omp for reduction(+:sum)
			for (i = 0; i < num_steps; i++) {
				x = (i + 0.5) * step;
				sum = sum + 4.0 / (1.0 + x * x);
			}

	}
		pi = sum * step;
	
	printf("\n pi with %ld steps is %lf\n ", num_steps, pi);
	
}
