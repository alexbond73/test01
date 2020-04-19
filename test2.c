#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define TRUE 1

char* arr;
int ctr = 1;
int ctr_divisor = pow(2, 25);
int i;

// arr = (char*)malloc(1 * sizeof(char));

int main() {
  while(TRUE) {
  ctr *= 2;
  if((ctr % ctr_divisor) == 0) printf("%u : %u\n", ctr*sizeof(char), ctr);
  char* arr = (char*) calloc(ctr, sizeof(char));
  if(arr == NULL) {
  	printf("Can't allocate %u of memory", ctr*sizeof(char));
	exit(0);
  }
  /* for(i = 0; i < ctr; i++) {
     arr[i] = 'i';
    } */
  } 
free(arr);
}
