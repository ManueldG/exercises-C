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
	int len = 0;
	for( int i = 0 ; i < 10 ; i++){
			
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

	f = fopen("dati.dat","rb");
	
	if( f != NULL){
		errno = 0;                                          
		fread(persone,sizeof(Persona),10,f);
		printf("\n caricato file %d",errno);  
		
		fclose(f);
	}                                          
	else{                                              
		printf("errore lettura %d\n",errno);     
		persone[0] = insert(60,"Mario","Rossi",'M');	
		persone[1] = insert(50,"Maria","Verdi",'F');
		persone[2] = insert(40,"Gianni","Bianchi",'M');
	
	}
	stampa(persone);
	

	f  = fopen("dati.dat","wb");

	if( f != NULL )
		fwrite(persone,sizeof(Persona),10,f);
	else
		printf("Errore scrittura");

	fclose(f);

//	f = fopen("dati.dat","rb");
	int fl =open("dati.dat",O_RDONLY);	
	char c;
	char ce,d,u;
	int i = 0;
	printf("\nprint\n");
do{
                        read(fl,&c,1);
			ce = (c / 100) + 48; 
			d = (( c % 100) / 10) + 48;			
			u = (( c % 100) % 10) + 48;
			u = (c % 10) + 48;
			write(1,&ce,1);
                        write(1,&d,1);
			write(1,&u,1);
			write(1,"\n",1);
			i++;		
                }while( i < 100 );


/*
	if( f != NULL){

		fread(persone,sizeof(Persona),10,f);

		printf("\n caricato file dati.dat \n");

		stampa(persone);
		do{
			read(fl,&c,1);
			write(1,&c,1);
		}while( c > 0  );

	}	
	else{
		printf("errore lettura");
	}	*/	
	}


