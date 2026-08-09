#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
/*
controllo stringhe 
!= null
se termina con \0
limitare output con %.10s o strnlen(str,10)
inserire \n 
leggere bit per bit
con write per la stringa

un modo per pulire una stringa potrebbe essere quello di stampare carattere per carattere e fermarsi se legge carattere fuori dal range dei caratteri visibili
*/

typedef struct persona {

	int eta;
	char *nome;
	char *cognome;
	char sesso;

} Persona;


Persona insert(int eta,char *nome,char *cognome,char sesso){

	Persona p = {eta,nome,cognome,sesso};

	return p;

};


void stampa(Persona p[10]){
//	int len = 0;
	for( int i = 0 ; i <= 10 ; i++){
			
		if(( &p[i] != NULL) && (p[i].nome != NULL) ){
			printf(" %d %.10s %.10s %c\n",p[i].eta,p[i].nome,p[i].cognome,p[i].sesso);
					
		}		
	}
}


int main(int argc,char **argv){
	

	Persona persone[10] = {

		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
		{0,"","",' '},
	};
	stampa(persone);
	FILE *f;

	f = fopen("dati.txt","r");
	
	if( f != NULL){
		errno = 0;                                          

		printf("\n caricato file %d-\n",errno);  
		int eta;
		char *nome;
		nome = calloc(sizeof(char),50);
		char *cognome;
		cognome = calloc(sizeof(char),50);
		char sesso;
		int i;
		for( i = 0 ; i <= 10 ; i++){

			fscanf(f,"%d,%s,%s,%c\n",&eta,nome,cognome,&sesso);
			printf("P%d %d %s %s %c\n",i,eta,nome,cognome,sesso);
			persone[i] = insert(eta,nome,cognome,sesso);			

		}
		printf("n %d\n",i);		
		fclose(f);
	}                                          
	else{                                              
		printf("errore lettura %d\n",errno);     
		persone[0] = insert(60,"Mario","Rossi",'M');	
		persone[1] = insert(50,"Maria","Verdi",'F');
		persone[2] = insert(40,"Gianni","Bianchi",'M');
	
	}

	stampa(persone);
	

	f  = fopen("dati.txt","w");
	int i = 0;
	if( f != NULL )
		while( i < 10 ){
		fprintf(f,"%d,%s,%s,%c\n",persone[i].eta,persone[i].nome,persone[i].cognome,persone[i].sesso);
		i++;		
		}
	else
		printf("Errore scrittura");

	fclose(f);


	}


