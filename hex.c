#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
char d2h(char c){
	char alp[6] = {'A','B','C','D','E','F'};
	char out = 0 ;
	if( c >= 0 && c <= 15 )
		if( c > 9 ){
			out = alp[ c - 10 ];
		}
		else{
			out = c + '0' ;
		}
	else
		printf("\n error value out of range\n");
		//errno strerror custom...
	return out;
}


char * tostr(char c){

	static char out[3];

	out[0] = d2h( c / 16);
	out[1] = d2h(c % 16);
	out[2] = '\0';

	return out;

}

int main(int argc, char ** argv){

	errno = 0;	

	FILE *f;	
	f = fopen(argv[1],"r");	


	if( (f == 0) || (errno > 0)  ){

		printf("\nErrore lettura file error: %d\n",errno);
		exit(1);

	}	
	

	char c =172;
	int i = 0;


	while( (c = fgetc(f)) != 255 && i < 10000 ){

		if( i % 7 == 0)
			printf("\n");
		printf("%1s:",tostr(c));
		if ( c >= 33  && c <= 126  )
			printf("%c ",c);
		else
			printf(". ");
		i++;

	}
	fclose(f);
	char one = c / 16;
	char two = c % 16;
	
	printf("\nchar\'%c\' ascii:%d hex:%s\n ",c,c,tostr(c));

}
