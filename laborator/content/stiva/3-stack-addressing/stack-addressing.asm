%include "../utils/printf32.asm"

%define NUM 5
   
section .text

extern printf
global main
main:
    mov ebp, esp

    ; TODO 1: replace every push by an equivalent sequence of commands (use direct addressing of memory. Hint: esp)
    mov ecx, NUM
push_nums:
    push ecx
    ;push ecx
    sub esp, 4
    mov dword[esp], ecx
    loop push_nums

    push 0
    push "mere"
    push "are "
    push "Ana "
    ;push 0

    sub esp, 4
    mov dword[esp], 0

    ;push "mere"
    sub esp, 4
    mov dword[esp], "mere"

    ;push "are "
    sub esp, 4
    mov dword[esp], "are "

    ;push "Ana "
    sub esp, 4
    mov dword[esp], "Ana "

    lea esi, [esp]
    PRINTF32 `%s\n\x0`, esi

    ; TODO 2: print the stack in "address: value" format in the range of [ESP:EBP]

    xor ebx, ebx
    mov ebx, esp

    xor ecx, ecx
    mov ecx, ebp
    sub ecx, esp

afisare:
    cmp ecx, 0
    je out
    PRINTF32 `%p \x0`, ebx
    PRINTF32 `%hhu\n\x0`, byte[ebx]
    add ebx, 1
    sub ecx, 1
    jmp afisare

    ; use PRINTF32 macro - see format above

out:
    ; TODO 3: print the string

 xor ebx, ebx
    mov ebx, esp

    xor ecx, ecx
    mov ecx, ebp
    sub ecx, esp

afisare_sir:
    cmp ecx, 0
    je out_sir
    xor eax, eax
    mov al, byte[ebx]
    cmp eax, 0
    je out_sir
    PRINTF32 `%c\x0`, byte[ebx]
    add ebx, 1
    sub ecx, 1
    jmp afisare_sir

    ; use PRINTF32 macro - see format above

out_sir:

    ; TODO 4: print the array on the stack, element by element.

    add ebx, 4
    xor ecx, ecx
    mov ecx, NUM

PRINTF32 `\n\x0`

afisare_vector:
    cmp ecx, 0
    je out_vector
    PRINTF32 `%hhu \x0`, byte[ebx]
    add ebx, 4
    sub ecx, 1
    jmp afisare_vector

out_vector:

    ; restore the previous value of the EBP (Base Pointer)
    mov esp, ebp

    ; exit without errors
    xor eax, eax
    ret