#include<stdio.h>

struct Gest{
	#define MEMBER(TYPE, NAME) TYPE NAME ;
	#include"ex5.h"
	#undef MEMBER
};

int main(){

	struct Gest Tmp;
	return 0;

}
