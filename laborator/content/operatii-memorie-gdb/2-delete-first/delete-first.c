#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* delete_first(char *s, char *pattern)
{
	int found_it = strstr(s,pattern) - s;
	char *s2 = strcpy(s + found_it, s + found_it + strlen(pattern));
	memcpy(s + found_it, s2, strlen(s2) );
	return s;
}

int main(){
	char s[] = "Ana are mere";
	char *pattern = "re";

	 printf("%s\n", delete_first(s, pattern));

	return 0;
}