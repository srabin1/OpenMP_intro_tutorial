/*
In this exercise we want to resolve the 
false sharing with the help of critical 
section and synchronize the code
*/
#include<omp.h>
#include<stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 2
//#define PAD 8// we remove this line since it is not workin 
//for different machine with different cache 


int main() {
	//we keep pi as global variable and change sum as local variable
	int nthreads;
	double pi = 0.0;
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);

#pragma omp parallel

	{
		int i, nthrds;
		double x;
		double sum;
		//thread Id or rank
		int ID = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		
		//this line is for master thread, to force inside of parallel region
		//to use the exact defined number of threads, because MPI by default 
		//would like to assign as less as possible thread
		if (ID == 0) nthreads = nthrds;
		for (i = ID, sum = 0.0; i < num_steps; i = i + nthreads) {
			x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}
	
		#pragma omp critical 
		pi += sum * step;
	}
	printf("\n pi with %ld steps is %lf\n ", num_steps, pi);
	//printf("with %d thread:\n", nthrds);

	printf("All done with hopefully %d threads: \n", nthreads);

}

/*
Atomic version:
summ = sum *step;
#pragma omp atomic
pi+= sum;
*/