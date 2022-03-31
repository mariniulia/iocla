#include <stdio.h>

int main(void)
{
	int v[] = {4, 1, 2, -17, 15, 22, 6, 2};
	int max;
	int i;
	int nr=sizeof(v)/sizeof(int);
	max = v[0];
	i = 1;
verifica:
 	if(i>=nr-1)
		goto gatavectorul;
	if(max < v[i])
		goto newmax;
	i++;
	goto verifica;


newmax:
	max=v[i];
	i++;
	goto verifica;

gatavectorul:
	printf("%d",max);
	
	(void) i;
	(void) max;
}
