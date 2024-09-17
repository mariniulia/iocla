
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mirror( char * s)
{

	int lenght = 0;
	while( *(s + lenght) ){
		lenght++;
	}
	// printf("%d", lenght);
	
	for(int i = 0 ; i < (lenght>>1); i++){
		char aux = *(s + i);
		// printf("prima data e : %c",*(s + i) );
		*(s + i) = *(s + lenght - i -1);
		// printf(" se schimba in : %c ", *(s + i) );
		*(s + lenght - i -1) = aux;
	}
	(void) s;
}

int main()
{
	char s[10];
	scanf("%s", s);
	mirror(s);
	printf("%s",s);
	return 0;
}

