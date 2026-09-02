#include<stdio.h>
#include<errno.h>
#include<stdlib.h>


int main(int argc, char ** argv){

	errno = 0;	

	FILE *f;	
	f = fopen(argv[1],"r");	


	if( (f == 0) || (errno > 0)  ){
		
		
		printf("\nErrore lettura file error: %d\n",errno);
		exit(1);

	}	
	

	char c = 0;
	int i = 0;
	char tmp;

	while( (c = fgetc(f)) != 255 && i < 20000 ){
		
		tmp=c;		
		
		if (c != ' '){
			if( ( c >= 'a' ) && (c <= 'z' ) ){
				c = c - 13;
				c = ( c < 'a' ) ? ( c + 26) : c;			
			}
			else if ( (c >= 'A') && (c <= 'Z' ) ){

				c = c - 13;
				c = ( c <= 'A'  ) ? c + 26 : c;

			}
		}
			
		printf("%c",c);
		i++;

	}
	fclose(f);
	printf("\n%d %c",('c' - 13),( 'c' - 13 ));
}
