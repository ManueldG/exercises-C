#include<stdio.h>
#include<stdlib.h>

/*
	definisce due macro una per definire il parametro e l'altra la funzione nella struct 
	includendo ex5.c inietto il codice che userà le macro  
*/
struct Gest{

	#define MEMBER(TYPE, NAME,INIT,PARAM) TYPE NAME ;
	#define FUNC(TYPE, NAME,INIT,PARAM) TYPE (*NAME) PARAM ;
	#include"ex5.h"
	#undef MEMBER
	#undef FUNC

};


/*
	includo il file delle funzioni mi sembra più pratico che includerlo nella compilazione includo gli header una sola volta
	da vedere le eventuali differenze 
*/
#include"functions.c"

int main(){
	/*
	credo che non userei mai una struttura del genere in un progetto mi serve a studiare alcune funzionalità del codice 
	qui dichiaro la struct per inizializzarla collego la funzione init al membro init cosi posso inizilaizzare la struttura usando la 	funzione interna
	*/

	struct Gest *Tmp;

	Tmp->init = &init;
	
	Tmp->init(Tmp);		
	
	//stampo la struct inizializzate
	printf("%d %d %s\n",Tmp->func(2,0),Tmp->id,Tmp->nome);
	
	//modifico dei valori ...
	Tmp->id = 20;

	//...rialloco memoria e copio la stringa e...
	Tmp = Tmp->str(Tmp, "abcdefghilmnopqrstuvz");
	
	//...la ristampo
	printf("%d %d %s\n",Tmp->func(3,0),Tmp->id,Tmp->nome);

	return 0;

}
