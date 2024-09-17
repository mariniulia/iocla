#include <stdio.h>
#include <stdlib.h>

void print_hexa(int number, int nr_bits)
{	int necesari=nr_bits;
	printf("0x");
	while(((necesari >>2 )<<2) ^  necesari ){
     necesari=necesari + 1;
	 printf("0");
	}
//  printf("nr biti : %d", nr_bits);
	for(int i=nr_bits-1; i >= 0;i--){
		if((number>>(4*i) == 15))
		printf("F");
		else if(number>>4*i == 14)
		printf("E");
		else if((number>>4*i) == 13)
		printf("D");
		else if((number>>4*i) == 12)
		printf("C");
		else if((number>>4*i )== 11)
		printf("B");
		else if((number>>4*i) == 10)
		printf("A");
		else if ((number>>4*i)<10)
		printf("%d" ,number>>(4*i));
	
		number=number-((number>>(4*i))<<(4*i));
		}
	
	printf("\n");
	(void) number;
	(void) nr_bits;
}

void print_binary(int number, int nr_bits)
{	int necesari=nr_bits;
	printf("0b");
	while(((necesari >>2 )<<2) ^  necesari ){
     necesari=necesari + 1;
	 printf("0");
	}

	for(int i=nr_bits -1; i >= 0;i--){
		if(number>>i){
		printf("1");
		number=number-((number>>i)<<i);
		}
		else
		printf("0");
	}
	printf("\n");
	(void) number;
	(void) nr_bits;
}

void check_parity(int *numbers, int n)
{	int nr_bits=0;
	for(int i = 0;i < n;i++){
		
		if(((*(numbers+i) >>1)<<1) ^ ( *(numbers+i) )  ) { //daca e impar
		while(*(numbers+i)>>(4*nr_bits))
			nr_bits++;
		print_hexa(*(numbers+i),nr_bits);
		nr_bits = 0;
		
		}else{
		
		while(*(numbers+i)>>nr_bits)
			nr_bits = nr_bits + 4;
		print_binary(*(numbers+i), nr_bits);
		nr_bits = 0;
		}
	}

	(void) numbers;
	(void) n;
}

int main()
{
	int n;
	scanf("%d", &n);
	int v[n];
	for(int i = 0;i < n;i++){
		scanf("%d", v+i);
	}
	check_parity(v,n);

	return 0;
}

