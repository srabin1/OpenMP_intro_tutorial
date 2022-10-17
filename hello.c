#include <omp.h>
#include <stdio.h>
int main ()  
{
	//#pragma says give me a bunch of threads, 
	//if we don't specify it, it give a defult number of threads
#pragma omp parallel
	{
		//ID is giving me an identifier for each thread from [0, #threads -1]
		int ID = omp_get_thread_num();
		printf("Hello%d", ID);
		printf(" World %d\n", ID);
	}
}
