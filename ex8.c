#include<stdio.h>
#include<unistd.h>

// -fsanitize=address
int main(int argv , char **argc){
	
	char x[] = {'C','i','a','o'};
	char y[] = {48,126,'C','i','a','o',7,200,5};	
	int i = 0;
	char in;
	  
	while (y[i]>=48 && y[i]<=126){
		write(1,&y[i],1);
		i++;
	}
	y[i] = '\0';
	printf("\n %lu %s\n \n",(long unsigned) y,y);	
	
	do{
		in = getchar();
		putchar(in);		
		printf(" -  ");
	}
	while(in  != '0');
//	fflush(stdin);
	//memset(ptr, 0, size)
	return 0;

}
