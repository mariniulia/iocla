#include <stdio.h>

int main(void)
{
	int arr[] =  {1, 2, 15, 51, 53, 66, 202, 7000};
	int x = arr[2]; /* 15 */
	int l = 0;
	int m;
	int r = sizeof(arr) / sizeof(int) - 1;
verifica:
	if(l>r)
		goto numaigasesti;
	m = l + (r - l) / 2;
        // Check if x is present at mid
        if (arr[m] == x)
            goto gasit;
 
        // If x greater, ignore left half
        if (arr[m] < x)
			goto cautadreapta;
        // If x is smaller, ignore right half
        else
			goto cautastanga;

goto numaigasesti;

cautadreapta:
	l = m + 1;
	goto verifica;
	
cautastanga:
	r = m - 1;
	goto verifica;


gasit:
printf("%d",arr[m]);
return 0;

numaigasesti:
printf("nu exista");
return 0;
	(void) x;
	(void) l;
	(void) r;
}
