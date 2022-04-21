%include "../utils/printf32.asm"

section .data
source_text: db "ABCABCBABCBABCBBBABABBCBABCBAAACCCB", 0
len equ $ - source_text
substring: db "BABC", 0
len2 equ $ - substring - 1
string_format db "%s", 10, 0
int_format db "%d", 10, 0
char_format db "%c", 10, 0
cod_1 dw 0
cod_2 dw 0

print_format: db "Substring found at index: %d", 10, 0

section .text
extern printf
global main

main:
    push ebp
    mov ebp, esp
    
    mov eax, dword[substring]
    mov dword[cod_1], eax
    mov edx, 32

    xor ecx, ecx
    jmp verify

add_ecx:
    add ecx, 1
    cmp edx, ecx
    jg verify
    cmp edx, ecx
    je leaving


verify:
    mov eax, dword[source_text + ecx]
    cmp dword[cod_1], eax
    je printing
    jmp add_ecx

printing:
    push ecx
    push int_format
    call printf
    add esp, 8
    cmp edx, ecx
    je leaving
    jmp add_ecx


leaving:
    leave
    ret

