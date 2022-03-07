#include <stdio.h>

void rotate_left(int *number, int bits)
{ 

	printf("numar: %d \n", *number);
	 int copie = *number;
	*number = *number << bits;
	printf("numar: %d \n", *number);
	printf(" copie: %d \n", copie);
	copie = copie >> (32-bits);
	printf(" copie modificata: %d \n", copie);
	*number = *number | copie;

	(void) number;
	(void) bits;
}

void rotate_right(int *number, int bits)
{
	 int copie=*number;
	*number = *number >> bits;
	printf("numar: %d \n", *number);
	printf(" copie: %d \n", copie);
	copie = copie << (32-bits);
	printf(" copie modificata: %d \n", copie);
	*number = *number | copie;

	(void) number;
	(void) bits;
}

int main()
{
	int number,bits;
	scanf("%d %d", &number , &bits);
	rotate_left(&number,bits);
	// rotate_right(&number,bits);
	printf("%d",number);


	return 0;
}

