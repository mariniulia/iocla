section .data
    before_format db "before %s", 13, 10, 0
    after_format db "after %s", 13, 10, 0
    mystring db "abcdefghij", 0

section .text

extern printf
global main

toupper:
    push ebp
    mov ebp, esp

 mov eax, [ebp + 8]
    xor ecx, ecx

iterate:
    xor ebx, ebx
    mov bl, byte[eax + ecx]
    cmp bl, 0
    je out
    sub bl, 32
    mov byte[eax + ecx], bl
    add ecx, 1
    jmp iterate

out:; TODO

    leave
    ret

main:
    push ebp
    mov ebp, esp

    push mystring
    push before_format
    call printf
    add esp, 8

    push mystring
    call toupper
    add esp, 4

    push mystring
    push after_format
    call printf
    add esp, 8

    leave
    ret
