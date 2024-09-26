#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void *find_max(void *arr, int n, int element_size,
				int (*compare)(const void *, const void *)) {
	void *max_elem = arr;
	for(int i=0;i<n;i++){
		if(compare(arr+i*4,max_elem))
		// printf("element : %d", *(int*)(arr+i*4));
		max_elem=arr+i*4;
	}

	(void) n;
	(void) element_size;
	(void) compare;

	return max_elem;
}


int compare_ints(const void *a, const void *b){
	// int* inta=(int *)a;
	// int* intb=(int *)b;
	for(int i=0;i<sizeof(int);i++){
		if(*(int*)(a+i)>*(int*)(b+i))
		return 1;
		if(*(int*)(a+i)>*(int*)(b+i))
		return 0;
	}
	return 0;

}


int main() {
	int n;
	scanf("%d", &n);

	int *arr = malloc(n * sizeof(*arr));

	for (int i = 0 ; i < n; ++i)
		scanf("%d", &arr[i]);

	int *res=(int *)find_max(arr,n,sizeof(*arr)/sizeof(int), compare_ints);
	printf("%d" , *res);

	free(arr);
	return 0;
}
