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

#ifndef _STDLIB_H 
	#error 1 - stdlib.h non inclusa
#endif
#pragma message ("1 ciao")




/*

estende strerror che arriva a 133
da 134 in poi posso usare codici di errore custom

*/
char* strerrorM(int);
void exitclean();


void exitclean(){
	/*
	crea log
	salva dati 
	chiudi files
	free puntatori
	*/

	perror("prova errore pers");
	
	printf("Error!  %s : n %d\n",strerrorM(errno),errno);	

}

/*
lista di messaggi che la trasformo in array che parte da 134
*/
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
		
}

char ** str2arr(char *str,char sep ){

	int i = 0;
	int r = 0;
	while( str[i] != '\0' ){

		if(str[i] == sep)
			r++;
		i++;

	}

	printf("caratteri %d separatori %d",i,r);
	char *out[r];
	char *string;
	string = calloc(sizeof(char),i);
	i = 0;
	r = 0;
	int c = 0;
	while(str[i] != '\0'){
		if(str[i] == '\n'){
			out[r] = calloc(sizeof(char),200);
			 strcpy(out[r],string);
			r++;
			c = 0;
			
		}
		else
			string[c] = str[i];
				
		i++;
		c++;		
			
	};
	printf("\n out %s stringa %s\n",out[1],string);
	

}
	
//	atexit(errtest);
//	errno = 0;
