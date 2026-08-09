#include<stdio.h>
#include<stdlib.h>


int lend(int n){

	int i = 1 ;
	
	while( n > 9){
		//printf("\n i: %d n:%d \n ",i,n);		
		n = n / 10;
		i++;	
	};	
	return i;
}

int * split(int n){
	
	int *out;
	out = calloc(sizeof(int),lend(n));
	int max = lend(n);
	

	for ( int i = max - 1; i >= 0 ; i--){

		out[i] = n % 10;		
		n = n / 10;
	}

	return out; 
}



int main( int argc,char **argv ){
	
	int n = atoi(argv[1]);
	int *s = split(n);
	int i = 0;
	int len = lend(n);
	printf("\n %d \n",n);

	for (i=0 ; i < len ; i++){

		
		printf("|%d",s[i]);
		
	
	}
		
	printf("|\n");

}
