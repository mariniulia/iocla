%include "../utils/printf32.asm"

section .data
    N dd 9 ; compute the sum of the first N fibonacci numbers
    print_format_1 db "Sum first %d", 10, 0
    print_format_2 db "fibo is %d", 10, 0
    ;FIBO dd 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    
section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    push dword [N]
    push print_format_1
    call printf
    add esp, 8
    
    ; TODO: calculate the sum of first N fibonacci numbers
    ;       (f(0) = 0, f(1) = 1)
    xor eax, eax     ;store the sum in eax
    
    ; use loop instruction

    mov ecx, dword[N]
    sub ecx, 2
    mov edx, 1
    mov ebx, 1

fibo_sum:
    ;mov ebx, dword[FIBO + ecx + 1]
    ;mov edx, dword[FIBO + ecx + 2]
    add edx, ebx
    mov eax, edx
    mov edx, ebx
    mov ebx, eax
    ;mov dword[FIBO + ecx], eax

    loop fibo_sum


    push eax
    push print_format_2
    call printf
    add esp, 8
    
    xor eax, eax
    leave
    ret