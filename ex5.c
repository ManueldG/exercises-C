#include<stdio.h>

struct Gest{
	#define MEMBER(TYPE, NAME,INIT) TYPE NAME ;
	#include"ex5.h"
	#undef MEMBER
};

int p(int x){
	return x*x;
}

void init(struct Gest *g){
	#define MEMBER(TYPE,NAME,INIT) g->NAME = INIT;
	#include"ex5.h"
	#undef MEMBER
}

int main(){

	struct Gest Tmp;
	//Tmp.func = &p;
	init(&Tmp);		
	printf("%d %s\n",Tmp.id,Tmp.nome);
	return 0;

}
