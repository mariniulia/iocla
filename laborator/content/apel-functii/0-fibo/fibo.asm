%include "../utils/printf32.asm"

%define NUM_FIBO 10

section .text

extern printf
global main
main:
    mov ebp, esp

    ; TODO - replace below instruction with the algorithm for the Fibonacci sequence
    sub esp, NUM_FIBO * 4

    mov ecx, NUM_FIBO
     xor edx, edx
	mov edi, 1
    mov esi, 0
    push esi
    push edi
foor:
	xor eax, eax
	add eax, esi
	add eax, edi
	push eax
	mov esi, edi
	mov edi, eax

	inc edx
	cmp edx, ecx
	jl foor

print:
    mov eax, dword [esp + (ecx - 1) * 4]
    mov eax, dword [esp + (ecx + 1) * 4]
    PRINTF32 `%d \x0`, eax
    dec ecx
    cmp ecx, 0

    PRINTF32 `\n\x0`
    mov esp, ebp
    xor eax, eax
    ret
