%include "printf32.asm"

section .text
    global main
    extern printf

main:
    ;cele doua multimi se gasesc in eax si ebx
    mov eax, 139
    mov ebx, 169
    PRINTF32 `%u\n\x0`, eax ; afiseaza prima multime
    PRINTF32 `%u\n\x0`, ebx ; afiseaza cea de-a doua multime

    ; TODO1: reuniunea a doua multimi
    mov ecx, eax
    or ecx, ebx
    PRINTF32 `%u\n\x0`, ecx ; afiseaza prima multime

    ; TODO2: adaugarea unui element in multime
    mov ecx, eax
    or ecx, 0x22
    PRINTF32 `%u\n\x0`, ecx ; afiseaza prima multime

    ; TODO3: intersectia a doua multimi
    mov ecx, eax
    mov edx, eax
    xor ecx, ebx
    sub edx,ecx
    PRINTF32 `%u\n\x0`, edx ; afiseaza prima multime

    ; TODO4: complementul unei multimi
    mov ecx, eax
    not ecx
    and ecx, 0x00000111 ;il aducem in 4 biti
    PRINTF32 `%u\n\x0`, ecx ; afiseaza prima multime

    ; TODO5: eliminarea unui element
    mov ecx, eax
    mov edx, 0x17
    not edx
    and ecx,edx
    PRINTF32 `%u\n\x0`, ecx ; afiseaza prima multime

    ; TODO6: diferenta de multimi EAX-EBX
    xor eax,ebx
    PRINTF32 `%u\n\x0`, eax

    xor eax, eax
    ret
