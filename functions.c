// TODO da includere in functions.h
/*
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#endif
*/
int p(int , int );

void init(struct Gest *);

int lengthStr(const char *);

struct Gest *str(struct Gest *, const char *);

//-----------------------------------------------------------------------

//funzione esempio
int p(int x, int y){
	return x*x;
}

//inizializza struct usando le istruzioni in ex5.h
void init(struct Gest *g){

	#define MEMBER(TYPE,NAME,INIT,PARAM) g->NAME = INIT;
	#define FUNC(TYPE, NAME,INIT,PARAM) g->NAME =  &INIT ;

	#include"ex5.h"
	#undef FUNC
	#undef MEMBER
}

//calcola la lunghezza di una stringa
int lengthStr(const char *string){

	int i = 0;
	while(string[i] != '\0')		
		i++;
	return i;

}

//copia una stringa nell'elemento della struct di tipo char* inutile ma era un modo per gestire i membri della struct in una funzione
struct Gest* str(struct Gest *g, const char *string){
	
	int i = g->lengthStr(string);

	g->nome = calloc( sizeof(char) , ( i + 1 ) );

	//s = realloc(s, sizeof(char) * ( i + 1 ) ); //dovrebbe riallocare un puntatore allocato da malloc non da errore ma calloc è fatto apposta per stringhe


	if (g->nome == NULL){
		printf("error memory");
		exit(1);
	}
	
	i = 0;
	
	while(string[i] != '\0'){
		
		g->nome[i] = string[i];		
	
		i++;

	}
	g->nome[i] = '\0';

	return g;

	
}
