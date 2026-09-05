#include <stdio.h>
#include <stdlib.h>

int * int2bin(int val){

int *out = malloc( sizeof(int) * 4 );

 for(int i = 0 ; i < 4 ; i++)
   out[i] = ( val >> i ) % 2;

 return out;
}
int xor(int a, int b){


   return ( ~a & b ) | ( a & ~b);
}

#define CONN 0b1000
#define DISCONN 0b0100
#define BUSY 0b0010 
#define MOD 0b0001


int main(){


	char flag = CONN;
	flag = flag | MOD | BUSY;
	flag = xor(0b1111 , flag);	
	int *out ;
	out = int2bin(flag);
	printf("%d %d %d %d", out[3], out[2], out[1], out[0]);

}


/*

1001 xor 0010 = 1011

a b
0 0 0
0 1 1
1 0 1
1 1 0


~ab + a~b  not a and b or a and not b

*/
