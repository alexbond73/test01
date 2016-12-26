#include <stdio.h>
#define TRUE 1

char* arr;
int ctr = 0;

int main() {
  while(TRUE) {
  ctr++;
  arr = realloc(arr, ctr * sizeof(char));
  }
free(arr);
}
