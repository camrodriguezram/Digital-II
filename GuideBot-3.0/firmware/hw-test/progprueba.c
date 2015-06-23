#include <stdlib.h>

//#include <math.h>
#include <string.h>
//#include <stdio.h>

int main(int argc,char *argv[]){
	
	char num[12];
	printf ("%s \n", "Escriba la operación a realizar");
	scanf ("%s",&num);
	
	char a[12],b[12];
	int i=0;
	for(i = 0;i<strlen(num);i=i+1){
		if(num[i] == '+'){
		 	strncpy(a,num,i);
		 	strncpy(b,num+(i+1),strlen(num)-i);
			int a1 =atoi(a);
			int b1 =atoi(b);
			int result=a1+b1;
			printf ("El resultado es %i: cuando %i es sumao a %i\n", result,a1,b1);
			break;
		}
		else{ 
		printf("yufj");
		}

	}
	
		
	return 0;
}	

/*

do{
int i = 0;
for(i = 0;;i=i+1){
c = uarrget();
v[i] = c;
}

}while(c == '\n');


*/
