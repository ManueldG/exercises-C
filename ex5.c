#include<stdio.h>

struct Gest{
	#define MEMBER(TYPE, NAME) TYPE NAME ;
	#include"ex5.h"
	#undef MEMBER
};

int p(int x){
	return x*x;
}

int main(){

	struct Gest Tmp;
	Tmp.func = &p;
	printf("%d\n",Tmp.func(4));
	return 0;

}
