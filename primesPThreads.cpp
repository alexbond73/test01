#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS     10
#define THREAD_LOAD 1000000
using namespace std;

struct prime_range {
    int min;
    int max;
    int total;
};

void* findPrime(void *threadarg)
{
	    int i, primes = 0;
	        struct prime_range *this_range;
	    this_range = (struct prime_range *) threadarg;

	        int minLimit =  this_range -> min ;
	    int maxLimit =  this_range -> max ;
	        int flag = false;
	    while (minLimit <= maxLimit) {
	            i = 2;
	            int lim = ceil(sqrt(minLimit));
	            while (i <= lim) {
	                if (minLimit % i == 0){
	                flag = true;
	                break;
	            }
	            i++;
	            }
	            if (!flag){
	                primes++;
	        }
	            flag = false;
	            minLimit++;
	        }
	        this_range ->total = primes;
	    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	    int numThreads = NUM_THREADS;
	    int threadLoad = THREAD_LOAD;
	    struct timespec start, finish;
            double elapsed;

	    clock_gettime(CLOCK_MONOTONIC, &start);

	    pthread_t threads[NUM_THREADS];
	    struct prime_range pr[NUM_THREADS];
	    int rc;
	    pthread_attr_t attr;
	    void *status;

	    switch(argc){
		    case 1:
		      break;
		    case 2: 
		      numThreads = atoi(argv[1]);
		    case 3:
		      numThreads = atoi(argv[1]);
		      threadLoad = atoi(argv[2]);
		    default:
		      break;
	    }		 

	    pthread_attr_init(&attr);
	    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	    for(int t=1; t<= numThreads; t++){
	            pr[t].min = (t-1) * threadLoad + 1;
	            pr[t].max = t*threadLoad;
	            rc = pthread_create(&threads[t], NULL, findPrime,(void *)&pr[t]);
	            if (rc){
	                printf("ERROR; return code from pthread_create() is %d\n", rc);
	            exit(-1);
	            }
	        }
	        int totalPrimesFound = 0;
	    // free attribute and wait for the other threads
	    pthread_attr_destroy(&attr);
	        for(int t=1; t<= numThreads; t++){
	                rc = pthread_join(threads[t], &status);
		      if (rc) {
			printf("Error:unable to join, %d" ,rc);
	            	exit(-1);
	  		}
	          totalPrimesFound += pr[t].total;
	        }
	    clock_gettime(CLOCK_MONOTONIC, &finish);
	    elapsed = (finish.tv_sec - start.tv_sec);
	    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	    printf("This machine calculated all %d prime numbers under %d in %lf seconds\n",totalPrimesFound, numThreads*threadLoad, elapsed);
	    pthread_exit(NULL);
}
