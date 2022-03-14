#include <stdio.h>

/**
 * Afisati adresele elementelor din vectorul "v" impreuna cu valorile
 * de la acestea.
 * Parcurgeti adresele, pe rand, din octet in octet,
 * din 2 in 2 octeti si apoi din 4 in 4.
 */

void print_char(int *v,int n){
    printf("MARIME V: %ld, ELEMENTE V: %ld \n", sizeof(v), sizeof(v)/sizeof(int));
unsigned char *char_ptr =(unsigned char*)v;
for(unsigned char i=0;i<n*4;i++){
    printf("%p -> 0x%x\n", char_ptr, *(char_ptr+i));
}
}

void print_short(int *v,int n){
short *short_ptr =(short*)v;
for(unsigned short i=0;i<n*2;i++){
    printf("%p -> 0x%x\n", short_ptr, *(short_ptr+i));
}
}

void print_int(int *v,int n){
int *int_ptr =v;
for(unsigned int i=0;i<n;i++){
    printf("%p -> 0x%x\n", int_ptr, *(int_ptr+i));
}
}


int main() {
    int v[] = {0xCAFEBABE, 0xDEADBEEF, 0x0B00B135, 0xBAADF00D, 0xDEADC0DE};
printf("MARIME V: %ld, ELEMENTE V: %ld \n", sizeof(v), sizeof(v)/sizeof(int));
printf("PENTRU CHAR \n");
 print_char(v,5);
 printf("PENTRU short \n");
 print_short(v,5);
 printf("PENTRU INT \n");
 print_int(v,5);
    (void) v;

    return 0;
}
