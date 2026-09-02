#include<stdarg.h>
#include<stdio.h>

void tryarg(int n,...){

	va_list ap;
	va_start(ap,n);
	printf("\n%d %d %d %d ",n,va_arg(ap,int),va_arg(ap,int),va_arg(ap,int));
	va_end(ap);
}

int main(){


	tryarg(1,7,4,8);
	return 0;
}
