#include<stdlib.h>
#include<errno.h>
#include<string.h>

#ifndef _STDLIB_H 
	#error 1 - stdlib.h non inclusa
#endif
#pragma message ("1 ciao")

void errtest(){
	errno = 1;
	perror("prova errore pers");
	
	printf("exit invocato %d\n",errno);	
}

int main(int argc, char *argv[] ) {
	
	atexit(errtest);
	errno =0;
	
	printf ("errore : %s\n",strerror(errno));
if (argc > 2)
	exit(1);

printf("fine\n");

return 0;

}
