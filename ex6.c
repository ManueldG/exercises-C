/*
errno 1 - 133

funzione reset errno -> errno = 0

funzione gestione errore
restituisco messaggio da funzioni std e magari per le funzioni custom

funzione controllo validita dati 
range dati validi o tipi validi

funzione preuscita da passare a atexit
salvare file aperti e chiuderli
salvare dati in uso e liberare memoria free
eventuali messaggi di chiusura o errore

*/


#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include"error.c"

#ifndef _STDLIB_H 
	#error 1 - stdlib.h non inclusa
#endif
#pragma message ("1 ciao")


//char* strerrorM(int);

void errtest(){
	/*
	crea log
	salva dati 
	chiudi files
	free puntatori
	*/
	
	errno = 12;
	perror("prova errore pers");
	
	printf("exit invocato %s : n %d\n",strerrorM(errno),errno);	
}

/*
lista di messaggi che la trasformo in array che parte da 134
*/
/*
char* strerrorM(int err){
	
	char *out[2]  ;
	#define CONC(NUM,MESS) out[NUM] = MESS;
	CONC(134,"prova 1");
	CONC(135,"prova 2");
	#undef CONC

	if(err >= 0 && err < 134)
		return strerror(err);
	else
		return out[err];
		
}*/

int main(int argc, char *argv[] ) {
	
	atexit(errtest);

	char *stringa = " eh di uff the tu g u g g dv by dv\n"
"tu f h f eh he si is di deve dv h dv dv dv dv bcc dv dv dv c\n"
"tu f h f eh he si is di deve dv h dv dv dv dv bcc dv dv dv c\n"
"tu f h f eh he si is di deve dv h dv dv dv dv bcc dv dv dv c\n"
"tu f h f eh he si is di deve dv h dv dv dv dv bcc dv dv dv c\n";
	str2arr(stringa,'\n');
	errno = 0;
	if(argc>=2 ){
		
		int err = atoi( argv[1]);
		if( err>=0 && err <= 233)
			printf("\n argv:%s err %d mess:%s\n",argv[1],err,strerrorM(err));	
	}
	printf ("errore : %s \n",strerrorM(0));

	
	errno = 0;// prima di chamare malloc resetto errno
	char *str;
	str = calloc(sizeof(char),50);
	
	if(str == NULL){// controllo se ha allocato la memoria al puntatore
		//in caso d'errore stampo errore e numero poi esco non è un'errore del programma risolvibile		
		printf("\n %s : %d\n",strerrorM(errno),errno);
		exit(errno);
		
	}

if (argc > 2)
	exit(1);
	
//printf("\n %s : %d\n",strerrorM(134),134);

printf("fine\n");

return 0;

}

