%include "printf32.asm"

section .text
    global main
    extern printf

main:
    mov eax, 4       ; vrem sa aflam al N-lea numar; N = 7
    mov ebx, 0
    mov ecx, 1
    mov edx, 0
start:
    cmp eax, 0
    jne addone
    je PRINTF32 `%d\n\x0`, ebx ; afiseaza numarul
    ret

addone:
    sub eax, 1  ;scadem pasul
    mov edx, ecx    ;valoarea mare e pastrata
    add ecx, ebx    ;valoarea mare e incementata cu cea precedenta
    mov ebx, edx    ;valoarea mare devine cea mica
    jmp start

