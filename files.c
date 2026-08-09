#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
 int value;
 char *name ;
 name = calloc(sizeof(char),50);

 char *surname;

surname = calloc(sizeof(char),50);

char gender;

 FILE *f;
 
 if( (f = fopen("dati.txt","r"))== NULL)
	printf("Error");
 else {
	for(int i = 0 ; i <= 10 ; i++){
	fscanf(f,"%d , %[^, ], %[^, ],  %c\n",&value,name,surname,&gender);
	printf("%d %s %s - %c\n",value,name,surname,gender);
	value = 0;
	strcpy(name, " ");
	strcpy(surname," ");
	gender = ' ';
}
fclose(f);
return 0;
} 


}
