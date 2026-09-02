#pragma  message( "RICORDATI: Questa sezione di codice va ottimizzata prima del rilascio!" )
#include<stdio.h>

typedef struct value{
	unsigned boo :2;
} Val;

typedef struct object Object;
typedef struct objects Objects;

struct object {

	int var;

	int (*func)(int);

};

struct objects {
	int count;
	Object obj;
};

//Prima struct
struct Posizione {
    int x;
    int y;
};

// Seconda struct
struct Fisica {
    int velocita;
    int accelerazione;
};

// Unione allo stesso livello
struct Giocatore {
    struct Posizione p; // Struttura anonima 1
    struct Fisica;    // Struttura anonima 2
    int salute;       // Campo specifico del Giocatore
};

int func(int n){
	return n * n;
	}

float media(int values[],int len){
	
	int sum;
	float out;
	for(int  x = 0 ; x < len ; x++)
		sum += values[x];
	
	out = sum / len;
	return out;	
}


int main(){
	Object num ;
	Objects o;

	Val n; 
	n.boo = 3;
	num.var = 5;
	o.obj.var = 7;
	
	num.func =  func;
	printf("ris = %d %d -> %d %d\n",num.func(num.var),n.boo,++n.boo,o.obj.var);

	float m = media((int[]){9,4,6,2,8},5);

	printf("la media è %.2f \n ",m);

	struct Giocatore eroe;

	eroe.p.x = 20;
	
	printf("eroe posizione %d\n",eroe.p.x);
	
	return 0;	

}
