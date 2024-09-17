#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen(const char *str)
{
	int contor=0;
	while ( *(str+contor) ){
	contor++;
	}
	return contor;
	
}

void equality_check(const char *str,int lenght)
{
	int contor=0;
 while(contor < lenght){
		if(!(*(str+contor)^*(str+contor+ (1<<contor)))){
			printf(" adresa 1 : %p ", str+contor);
			printf("  adresa 2 : %p \n", str+contor + (1<<contor));
		}
		contor++;
}
}

int main(void)
{
	char str[156];
	scanf("%s", str);
	int lenght = my_strlen(str);
	printf("%d \n", lenght);
	equality_check(str,lenght);

	return 0;
}

