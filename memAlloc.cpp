#include <stdio.h>
#include <stdlib.h>

#define MINREQ      0xFFF   // arbitrary minimum

int main(void)
{
	    unsigned int required = ((unsigned int)-1); // adapt to native uint
	    char *mem = NULL; 
	    while (mem == NULL) {
	            printf ("Required %X\n", required);
	            mem = malloc (required);
	            if ((required = required/4*3) < MINREQ) {
	                if (mem) free (mem);
	                printf ("Cannot allocate enough memory\n");
	                return (1);
	            }
	        }

	    free (mem);
	    
	    // Data = (int*) calloc (i,sizeof(int));
	    // mem = malloc (required);
	    mem = (char*) calloc (required, sizeof(char));
	        if (mem == NULL) {
	        printf ("Cannot enough allocate memory\n");
	        return (1);
	        }
	    printf ("Memory size allocated = %X\n", required);
	    while(true){}
	    free (mem);
	    return 0;
}
