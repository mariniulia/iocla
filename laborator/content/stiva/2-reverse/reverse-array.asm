%include "../utils/printf32.asm"

%define ARRAY_LEN 7

section .data

input dd 122, 184, 199, 242, 263, 845, 911
output times ARRAY_LEN dd 0

section .text

extern printf
global main
main:

    ; TODO push the elements of the array on the stack
    ; TODO retrieve the elements (pop) from the stack into the output array
    mov ecx, ARRAY_LEN
    sub ecx, 1

punem:
    cmp ecx, 0
    jl out
    push dword[input + ecx * 4]
    sub ecx, 1
    jmp punem

out:
    ; TODO retrieve the elements (pop) from the stack into the output array

    xor ecx, ecx
    mov ecx, ARRAY_LEN
    sub ecx, 1

scoatem:
    cmp ecx, 0
    jl gata
    pop eax
    mov dword[output + ecx * 4], eax
    sub ecx, 1
    jmp scoatem

gata:

    PRINTF32 `Reversed array: \n\x0`
    xor ecx, ecx

print_array:
    mov edx, [output + 4 * ecx]
    PRINTF32 `%d\n\x0`, edx
    inc ecx
    cmp ecx, ARRAY_LEN
    jb print_array
    xor eax, eax
    ret
