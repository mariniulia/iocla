%include "../utils/printf32.asm"

section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    mov eax, 211    ; to be broken down into powers of 2
    mov ebx, 1      ; stores the current power
    mov ecx, eax
shift:
    shl ebx,1
    cmp ecx,1
    je done
    cmp ecx,ebx
    jl printit
    jg shift

printit:
    shr ebx, 1
    PRINTF32 `%d \x0`, ebx
    sub ecx,ebx
    mov ebx,1
    jmp shift

    ; TODO - print the powers of 2 that generate number stored in EAX
done:
    PRINTF32 `%d \x0`, ecx
    leave
    ret
