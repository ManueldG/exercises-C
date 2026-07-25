

#include <stdio.h>
#include <stdlib.h>

int main(int argc ,char** argv){

	int *ptr;
	
	ptr = malloc(sizeof(int) * 10);
	*ptr = 6;
	*(ptr + 1) = 8;
	*(ptr + 9) = 3;
	for(int i = 0 ; i < 10 ; i++) 
		printf(" %d \n",*(ptr+i));
	return 0;

}
