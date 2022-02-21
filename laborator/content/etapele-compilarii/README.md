# Laborator 03: Compilare

TODO: Start text

Etapele prin care trece un program din momentul în care este scris până când este rulat ca un proces sunt, in ordine:

- preprocesare
- compilare
- asamblare
- link editare

În imaginea de mai jos sunt reprezentate si detaliate aceste etape:

![phases-full.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/phases-full.png?cache=)

În etapa de `compilare` codul este tradus din cod de nivel înalt în limbaj de asamblare. Limbajul de asamblare este
o formă human-readable a ce ajunge procesorul să execute efectiv. Dacă programele scrise în limbaje de nivel înalt ajung
să fie portate ușor pentru procesoare diferite (arm, powerpc, x86, etc.), cele scrise în limbaj de asamblare sunt
implementări specifice unei anumite arhitecturi. Limbaje de nivel înalt reprezintă o formă mai abstractă de rezolvare a
unei probleme, din punctul de vedere al unui procesor, motiv pentru care și acestea trebuie traduse în limbaj de asamblare
în cele din urmă, pentru a se putea ajunge la un binar care poate fi rulat. Mai multe detalii în laboratorul următor.

Majoritatea compilatoarelor oferă opțiunea de a genera și un fișier cu programul scris în limbaj de asamblare.

>**NOTE**: În cazul compilatorului `gcc` este de ajuns să adăugați flag-ul `-S` și vă va genera un
fișier `*.s` cu codul aferent. În arhiva de `TODO` aveți un exemplu de trecere a unui program
foarte simplu `hello.c` prin cele patru faze. Îl puteți testa pe un sistem Unix/Linux și pe un sistem Windows cu suport de MinGW.
```shell
$ make
cc  -E -o hello.i hello.c
cc -Wall -S -o hello.s hello.i
cc  -c -o hello.o hello.s
cc  -o hello hello.o

$ ls
Makefile  hello  hello.c  hello.i  hello.o  hello.s

$ ./hello
Hello, World!

$ tail -10 hello.i


# 5 "hello.c"
int main(void)
{
 puts("Hello, World!");

 return 0;
}

$ cat hello.s
	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	"Hello, World!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 5.2.1-17) 5.2.1 20150911"
	.section	.note.GNU-stack,"",@progbits

$ file hello.o
hello.o: ELF 64-bit LSB relocatable, x86-64, [...]

$ file hello
hello: ELF 64-bit LSB executable, x86-64, [...]

$ objdump -d hello.o

hello.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	bf 00 00 00 00       	mov    $0x0,%edi
   9:	e8 00 00 00 00       	callq  e <main+0xe>
   e:	b8 00 00 00 00       	mov    $0x0,%eax
  13:	5d                   	pop    %rbp
  14:	c3                   	retq
```

Pentru a genera sintaxa intel pe 32 de biți, se pot folosi aceste opțiuni:
```shell
cc -Wall -m32 -S -masm=intel  -o hello.s hello.i
```

## Assembly / Asamblare

Assembly / Asamblare este penultima etapă a procesului de compilare în sens larg.
În urma finalizării acestei etape rezultatul va fi crearea a unul sau mai multe fișiere obiect. Fișierele obiect pot conține mai multe lucruri,
printre care:
1. nume de simboluri
1. constante folosite în cadrul programului
1. cod compilat
1. valori de tip import/export care vor fi „rezolvate” în etapa de linking

Pentru a crea un fișier obiect în cazul în care se utilizează compilatorul `gcc` se folosește opțiunea `-c` așa cum puteți vedea și în secțiunea [Invocarea linker-ului](#invocarea-linker-ului) de mai jos.

## Linking / Legare

Linking / Legare este ultima etapă a procesului de compilare în sens larg.
La finalul acestei etape va rezulta un fișier executabil prin unificarea(„legarea”) mai multor fișiere obiect care pot avea la bază limbaje de 
programare de nivel înalt diferite; tot ceea ce contează este ca fișierele obiect să fie create în mod corespunzător pentru ca linker-ul să le 
poată „interpreta”.

Pentru a obține un fișier executabil din fișiere obiect, linker-ul realizează următoarele acțiuni:
1. rezolvarea simbolurilor (*symbol resolution*): localizarea simbolurilor nedefinite ale unui fișier obiect în alte fișiere obiect
1. unificarea secțiunilor: unificarea secțiunilor de același tip din diferite fișiere obiect într-o singură secțiune în fișierul executabil
1. stabilirea adreselor secțiunilor și simbolurilor (*address binding*): după unificare se pot stabili adresele efective ale simbolurilor în cadrul fișierului executabil
1. relocarea simbolurilor (*relocation*): odată stabilite adresele simbolurilor, trebuie actualizate, în executabil, instrucțiunile și datele care referă adresele acelor simboluri
1. stabilirea unui punct de intrare în program (*entry point*): adică adresa primei instrucțiuni ce va fi executată

## Invocarea linker-ului

Linker-ul este, în general, invocat de utilitarul de compilare (`gcc`, `clang`, `cl`).
Astfel, invocarea linker-ului este transparentă utilizatorului.
În cazuri specifice, precum crearea unei imagini de kernel sau imagini pentru sisteme încorporate, utilizatorul va invoca direct linkerul.

Dacă avem un fișier `app.c` cod sursă C, vom folosi compilatorul pentru a obține fișierul obiect `app.o`:
```
gcc -c -o app.o app.c
```
Apoi pentru a obține fișierul executabil `app` din fișierul obiect `app.o`, folosim tot utilitarul `gcc`:
```
gcc -o app app.o
```
În spate, `gcc` va invoca linker-ul și va construi executabilul `app`.
Linker-ul va face legătura și cu biblioteca standard C (libc).

Procesul de linking va funcționa doar dacă fișierul `app.c` are definită funcția `main()`, funcția principală a programului.
Fișierele linkate trebuie să aibă o singură funcție `main()` pentru a putea obține un executabil.

Dacă avem mai multe fișiere sursă C, invocăm compilatorul pentru fiecare fișier și apoi linker-ul:
```
gcc -c -o helpers.o helpers.c
gcc -c -o app.o app.c
gcc -o app app.o helpers.o
```
Ultima comandă este comanda de linking, care leagă fișierele obiect `app.o` și `helpers.o` în fișierul executabil `app`.

În cazul fișierelor sursă C++, vom folosi comanda `g++`:
```
g++ -c -o helpers.o helpers.cpp
g++ -c -o app.o app.cpp
g++ -o app app.o helpers.o
```
Putem folosi și comanda `gcc` pentru linking, cu precizarea linkării cu biblioteca standard C++ (libc++):
```
gcc -o app app.o helpers.o -lstdc++
```

Utilitarul de linkare este, în Linux, `ld` și este invocat în mod transparent de `gcc` sau `g++`.
Pentru a vedea cum este invocat linker-ul, folosim opțiunea `-v` a utilitarului `gcc`, care va avea un rezultat asemănător cu:
```
/usr/lib/gcc/x86_64-linux-gnu/7/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/7/liblto_plugin.so
-plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/7/lto-wrapper -plugin-opt=-fresolution=/tmp/ccwnf5NM.res
-plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc
-plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_i386 --hash-style=gnu
--as-needed -dynamic-linker /lib/ld-linux.so.2 -z relro -o hello
/usr/lib/gcc/x86_64-linux-gnu/7/../../../i386-linux-gnu/crt1.o
/usr/lib/gcc/x86_64-linux-gnu/7/../../../i386-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/7/32/crtbegin.o
-L/usr/lib/gcc/x86_64-linux-gnu/7/32 -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../i386-linux-gnu
-L/usr/lib/gcc/x86_64-linux-gnu/7/../../../../lib32 -L/lib/i386-linux-gnu -L/lib/../lib32 -L/usr/lib/i386-linux-gnu
-L/usr/lib/../lib32 -L/usr/lib/gcc/x86_64-linux-gnu/7 -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../i386-linux-gnu
-L/usr/lib/gcc/x86_64-linux-gnu/7/../../.. -L/lib/i386-linux-gnu -L/usr/lib/i386-linux-gnu hello.o -lgcc --push-state
--as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state
/usr/lib/gcc/x86_64-linux-gnu/7/32/crtend.o /usr/lib/gcc/x86_64-linux-gnu/7/../../../i386-linux-gnu/crtn.o
COLLECT_GCC_OPTIONS='-no-pie' '-m32' '-v' '-o' 'hello' '-mtune=generic' '-march=i686'
```
Utilitarul `collect2` este, de fapt, un wrapper peste utilitarul `ld`.
Rezultatul rulării comeznii este unul complex.
O invocare "manuală" a comenzii `ld` ar avea forma:
```
ld -dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -o app /usr/lib32/crt1.o /usr/lib32/crti.o app.o helpers.o -lc /usr/lib32/crtn.o
```
Argumentele comenzii de mai sus au semnificația:
* `-dynamic-linker /lib/ld-linux.so.2`: precizează loaderul / linkerul dinamic folosit pentru încărcarea executabilului dinamic
* `-m elf_i386`: se linkează fișiere pentru arhitectura x86 (32 de biți, i386)
* `/usr/lib32/crt1.o`, `/usr/lib32/crti.o`, `/usr/lib32/crtn.o`: reprezintă biblioteca de runtime C (`crt` - *C runtime*) care oferă suportul necesar pentru a putea încărca executabilul
* `-lc`: se linkează biblioteca standard C (libc)

## Inspectarea fișierelor

Pentru a urmări procesul de linking, folosim utilitare de analiză statică precum `nm`, `objdump`, `readelf`.

Folosim utilitarul `nm` pentru a afișa simbolurile dintr-un fișier obiect sau un fișier executabil:
```
$ nm hello.o
00000000 T main
         U puts

$ nm hello
0804a01c B __bss_start
0804a01c b completed.7283
0804a014 D __data_start
0804a014 W data_start
08048370 t deregister_tm_clones
08048350 T _dl_relocate_static_pie
080483f0 t __do_global_dtors_aux
08049f10 t __do_global_dtors_aux_fini_array_entry
0804a018 D __dso_handle
08049f14 d _DYNAMIC
0804a01c D _edata
0804a020 B _end
080484c4 T _fini
080484d8 R _fp_hw
08048420 t frame_dummy
08049f0c t __frame_dummy_init_array_entry
0804861c r __FRAME_END__
0804a000 d _GLOBAL_OFFSET_TABLE_
         w __gmon_start__
080484f0 r __GNU_EH_FRAME_HDR
080482a8 T _init
08049f10 t __init_array_end
08049f0c t __init_array_start
080484dc R _IO_stdin_used
080484c0 T __libc_csu_fini
08048460 T __libc_csu_init
         U __libc_start_main@@GLIBC_2.0
08048426 T main
         U puts@@GLIBC_2.0
080483b0 t register_tm_clones
08048310 T _start
0804a01c D __TMC_END__
08048360 T __x86.get_pc_thunk.bx
```

Comanda `nm` afișează trei coloane:
* adresa simbolului
* secțiunea și tipul unde se găsește simbolul
* numele simbolului

Un simbol este numele unei variabile globale sau a unei funcții.
Este folosit de linker pentru a face conexiunile între diferite module obiect.
Simbolurile nu sunt necesare pentru executabile, de aceea executabilele pot fi stripped.

Adresa simbolului este, de fapt, offsetul în cadrul unei secțiuni pentru fișierele obiect.
Și este adresa efectivă pentru executabile.

A doua coloana precizează secțiunea și tipul simbolului.
Dacă este vorba de majusculă, atunci simbolul este exportat, este un simbol ce poate fi folosit de un alt modul.
Dacă este vorba de literă mică, atunci simbolul nu este exportat, este propriu modulului obiect, nefolosibil în alte module.
Astfel:
* `d`: simbolul este în zona de date inițializate (`.data`), neexportat
* `D`: simbolul este în zona de date inițializate (`.data`), exportat
* `t`: simbolul este în zona de cod (`.text`), neexportat
* `T`: simbolul este în zona de cod (`.text`), exportat
* `r`: simbolul este în zona de date read-only (`.rodata`), neexportat
* `R`: simbolul este în zona de date read-only (`.rodata`), exportat
* `b`: simbolul este în zona de date neinițializate (`.bss`), neexportat
* `B`: simbolul este în zona de date neinițializate (`.bss`), exportat
* `U`: simbolul este nedefinit (este folosit în modulul curent, dar este definit în alt modul)

Alte informații se găsesc în pagina de manual a utilitarul `nm`.

Cu ajutorul comenzii `objdump` dezasamblăm codul fișierelor obiect și a fișierelor executabile.
Putem vedea, astfel, codul în limbaj de asamblare și funcționarea modulelor.

Comanda `readelf` este folosită pentru inspectarea fișierelor obiect sau executabile.
Cu ajutorul comenzii `readelf` putem să vedem headerul fișierelor.
O informație importantă în headerul fișierelor executabile o reprezintă entry pointul, adresa primei instrucțiuni executate:
```
$ readelf -h hello
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x8048310
  Start of program headers:          52 (bytes into file)
  Start of section headers:          8076 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         9
  Size of section headers:           40 (bytes)
  Number of section headers:         35
  Section header string table index: 34
```

Cu ajutorul comenzii `readelf` putem vedea secțiunile unui executabil / fișier obiect:
```
$ readelf -S hello
There are 35 section headers, starting at offset 0x1f8c:
Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        08048154 000154 000013 00   A  0   0  1
  [ 2] .note.ABI-tag     NOTE            08048168 000168 000020 00   A  0   0  4
  [ 3] .note.gnu.build-i NOTE            08048188 000188 000024 00   A  0   0  4
[...]
```

Tot cu ajutorul comenzii `readelf` putem lista (*dump*) conținutul unei anumite secțiuni:
```
$ readelf -x .rodata hello

Hex dump of section '.rodata':
  0x080484d8 03000000 01000200 48656c6c 6f2c2057 ........Hello, W
  0x080484e8 6f726c64 2100                       orld!.
```

TODO: Exercises

<!-- 
În acest laborator, vom trece prin fiecare nivel de procesare al unui limbaj de nivel înalt și prin toolchain-ul
pe care îl vom folosi de acum încolo.

## C basics: GOTOs

Un concept mai puțin abordat în tutoriale de C este instrucțiunea goto. Prin instrucțiunea goto, un program poate
sări în puncte intermediare în cadrul unei funcții. Aceste puncte intermediare se numesc label-uri (etichete).
Din punct de vedere al sintaxei, o eticheta consta dintr-un nume, urmat de caracterul `:`.

Un exemplu de cod: 

 
 ```C
#include <stdio.h>

int main()
{
    int i, j, k;
    /* some code */
do_some_work:
    /* some other code */
    work();
    if (any_work())
        goto do_some_work;
    /* some code */
    return 0;
}
```

Programul execută un job prin work(). În caz că mai sunt alte joburi neterminate, executia programului sare la
eticheta do_some_work. do_some_work marcheaza punctul din program în care începe procesarea unui nou job. Pentru a
sări la acest punct se folosește instrucțiunea goto urmată de numele etichetei declarate. Prin diferite combinații
de if-uri si goto-uri se pot echivala alte instrucțiuni din C, cum ar fi else, for si while.

Codul dat exemplu mai sus ar putea fi un candidat care să înlocuiască o instrucțiune `do { … } while ();`:

```C
#include <stdio.h>
 
int main()
{
    int i, j, k;
    /* some code */
    do {
        /* some other code */
        work();
    } while (any_work());
    /* some code */
    return 0;
}
```

### The "WHYs" of goto

Această instrucțiune nu doar că adesea lipsește din tutorialele de C, dar se fac
recomandări împotriva abordării ei deoarece de cele mai multe ori duce la cod ofuscat
(greu de înțeles, întreținut și depanat). Există totuși cazuri în care este folosita.
În codul kernel-ului de Linux (exemplu), instrucțiunile de goto sunt folosite ca o formă
de try-catch din limbaje de nivel mai înalt (precum C++, Java, C#, etc.). Exemplu:

```C
int process_data_from_mouse_device(...)
{
    int err;
    int x, y;
 
    /* >>try<< instructions */
    err = init_communication_with_mouse();
    if (err)
        goto error;
 
    err = get_x_coord_from_mouse(&x);
    if (err)
        goto error;
 
    err = get_y_coord_from_mouse(&y);
    if (err)
        goto error;
 
    err = announce_upper_layers_of_mouse_movement(x, y);
    if (err)
        goto error;
 
    err = close_communication_with_mouse();
    if (err)
        goto error;
 
    return 0;
 
    /* >>catch<< instructions' exceptions */
error:
    print_message("Failed to get data from mouse device. Error = %d", err);
    return err;
}
```

Acest cod încearcă să proceseze datele venite de la un mouse și să le
paseze altor părți superioare din kernel care le-ar putea folosi. În caz că apare vreo
eroare, se afișează un mesaj de eroare și se termină procesarea datelor. Codul pare corect,
dar nu este complet. Nu este complet pentru că în caz că apare o eroare în mijlocul funcției,
comunicația cu mouse-ul este lăsată deschisă. O variantă îmbunătățită ar fi următoarea:

```C
int process_data_from_mouse_device(...)
{
    int err;
    int x, y;
 
    /* >>try<< instructions */
    err = init_communication_with_mouse();
    if (err)
        goto error;
 
    err = get_x_coord_from_mouse(&x);
    if (err)
        goto error_close_connection;
 
    err = get_y_coord_from_mouse(&y);
    if (err)
        goto error_close_connection;
 
    err = announce_upper_layers_of_mouse_movement(x, y);
    if (err)
        goto error_close_connection;
 
    err = close_communication_with_mouse();
    if (err)
        goto error;
 
    return 0;
 
    /* >>catch<< instructions' exceptions */
error_close_connection:
    close_communication_with_mouse();
error:
    print_message("Failed to get data from mouse device. Error = %d", err);
    return err;
}
```

În varianta îmbunătățită, dacă apare o eroare, se face și o parte de curățenie:
conexiunea cu mouse-ul va fi închisă, și apoi codul va continua cu tratarea generală a oricărei
erori din program (afișarea unui mesaj de eroare).

>**NOTE**: De ce abordează acest curs/laborator un astfel de subiect?<br>
Când vom studia limbajul de asamblare vom observa că o bună parte din workflow seamănă cu un program format din goto-uri, 
chiar dacă majoritatea instrucțiunilor unui limbaj de nivel înalt, chiar și precum C, sunt inexistente. Gândirea și
programarea cu goto-uri ne pregătește pentru lucrul în limbajul de asamblare.

>**WARNING**: În orice alt caz, această formă de programare ar trebui evitată pe cât posibil. 
![goto.png]( https://imgs.xkcd.com/comics/goto.png)

## De la C la program în rulare

Etapele prin care trece un program din momentul în care este scris până când este rulat ca un proces sunt, in ordine:

- preprocesare
- compilare
- asamblare
- link editare

În imaginea de mai jos sunt reprezentate si detaliate aceste etape:

![phases-full.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/phases-full.png?cache=)

În etapa de `compilare` codul este tradus din cod de nivel înalt în limbaj de asamblare. Limbajul de asamblare este
o formă human-readable a ce ajunge procesorul să execute efectiv. Dacă programele scrise în limbaje de nivel înalt ajung
să fie portate ușor pentru procesoare diferite (arm, powerpc, x86, etc.), cele scrise în limbaj de asamblare sunt
implementări specifice unei anumite arhitecturi. Limbaje de nivel înalt reprezintă o formă mai abstractă de rezolvare a
unei probleme, din punctul de vedere al unui procesor, motiv pentru care și acestea trebuie traduse în limbaj de asamblare
în cele din urmă, pentru a se putea ajunge la un binar care poate fi rulat. Mai multe detalii în laboratorul următor.

Majoritatea compilatoarelor oferă opțiunea de a genera și un fișier cu programul scris în limbaj de asamblare.

>**NOTE**: În cazul compilatorului `gcc` este de ajuns să adăugați flag-ul `-S` și vă va genera un
fișier `*.s` cu codul aferent. În arhiva de `TODO` aveți un exemplu de trecere a unui program
foarte simplu `hello.c` prin cele patru faze. Îl puteți testa pe un sistem Unix/Linux și pe un sistem Windows cu suport de MinGW.
```shell
$ make
cc  -E -o hello.i hello.c
cc -Wall -S -o hello.s hello.i
cc  -c -o hello.o hello.s
cc  -o hello hello.o

$ ls
Makefile  hello  hello.c  hello.i  hello.o  hello.s

$ ./hello
Hello, World!

$ tail -10 hello.i


# 5 "hello.c"
int main(void)
{
 puts("Hello, World!");

 return 0;
}

$ cat hello.s
	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	"Hello, World!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 5.2.1-17) 5.2.1 20150911"
	.section	.note.GNU-stack,"",@progbits

$ file hello.o
hello.o: ELF 64-bit LSB relocatable, x86-64, [...]

$ file hello
hello: ELF 64-bit LSB executable, x86-64, [...]

$ objdump -d hello.o

hello.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	bf 00 00 00 00       	mov    $0x0,%edi
   9:	e8 00 00 00 00       	callq  e <main+0xe>
   e:	b8 00 00 00 00       	mov    $0x0,%eax
  13:	5d                   	pop    %rbp
  14:	c3                   	retq
```

Pentru a genera sintaxa intel pe 32 de biți, se pot folosi aceste opțiuni:
```shell
cc -Wall -m32 -S -masm=intel  -o hello.s hello.i
```


## Toolchain

În cadrul laboratoarelor vom folosi:
- asamblorul [NASM](https://www.nasm.us/)
- linkerul din cadrul suitei gcc

Pentru analiza codului si debugging vom folosi `gdb` si `Ghidra`.

## Ghidra

**Ghidra** este o unealtă foarte utilă pentru investigarea programelor si `reverse engineering`.

#### Dezasamblare
Procesul de dezasamblare este utilizat pentru obținerea unui fișier care conține cod de asamblare,
pornind de la un fișier binar. Acest proces este întotdeauna posibil, deoarece codul mașină specific
procesorului are o corespondență directă cu codul de asamblare. De exemplu, operația `add eax, 0x14`,
prin care la valoarea registrului eax se adaugă 20, se reprezintă întotdeauna folosind codul
binar `83 c0 14`.


#### Decompilare
Utilitarul Ghidra poate fi folosit chiar și pentru decompilare. Decompilatorul poate fi folosit
pentru a obține codul sursă într-un limbaj (relativ) de nivel înalt, care atunci când va fi
compilat va produce un executabil al cărui comportament va fi la fel ca executabilul original.
Prin comparație, un dezasamblor traduce un program executabil în limbaj de asamblare în mod exact,
pentru că există relația de 1:1 între cod mașină și limbaj de asamblare.<br>

Veți utiliza cele două opțiuni în cadrul laboratorului de astăzi, pentru a analiza niște binare simple.

>**WARNING**:
În cadrul laboratoarelor vom folosi repository-ul de git al materiei
IOCLA - [https://github.com/systems-cs-pub-ro/iocla](https://github.com/systems-cs-pub-ro/iocla).
Repository-ul este clonat pe desktop-ul
mașinii virtuale. Pentru a îl actualiza, folosiți comanda `git pull origin master` din interiorul
directorului în care se află repository-ul (`~/Desktop/iocla`). Recomandarea este să îl actualizați
cât mai frecvent, înainte să începeți lucrul, pentru a vă asigura că aveți versiunea cea mai recentă.
Dacă doriți să descărcați repository-ul în altă locație, folosiți comanda
`git clone https://github.com/systems-cs-pub-ro/iocla ${target}`.
Pentru mai multe informații despre folosirea utilitarului `git`, urmați ghidul de la [Git Immersion](https://gitimmersion.com/).

### 1. Online C Compiling

Un tool interesant pentru a observa cum se traduce codul C în limbaj de asamblare este Compiler Explorer.

1. Intrați pe [Compiler Explorer](https://gcc.godbolt.org/).
2. Încărcați programul “sum over array” din exemple (accesibile folosind butonul de load, în formă de dischetă).
3. Asigurați-vă că `x86-64 gcc 4.8.2` este selectat la `Compiler:`.
4. Folosiți opțiunea `-m32` (la `Compiler options`) pentru a afișa cod în limbaj de asamblare pe 32 de biți (față de 64 de biți în mod implicit).
5. Dacă vedeți mesajul `<Compilation failed>`, adăugați opțiunea `-std=c99`.
6. În continuare codul este destul de greoi. Pentru a putea fi mai human-readable adăugați opțiunea `-O2` la opțiunile de compilare (`Compiler options`).
7. Se poate observa existența simbolurilor `.L3:` și `.L4:`. Acestea reprezintă puncte fixe în program, label-uri, destul de asemănătoare cu ceea ce se găsește și în C.
8. Treceți, pe rând, prin compilatoarele corespunzătoare următoarelor arhitecturi: ARM, ARM64, AVR, PowerPC. `Atenție`: pentru ARM, ARM64 și AVR va trebuie să renunțați la flag-ul -m32 setat anterior. Se poate observa cum codul generat diferă de la o arhitectură la alta.
9. Mai încercați și următoarele compilatoare: `clang` și `icc`. După cum se poate observa, deși este același cod C și aceeași arhitectură, codul generat diferă. Acest lucru se întâmplă pentru că fiecare compilator poate avea o strategie de optimizare și generare de cod diferită.

>**NOTE**:
[clang](https://clang.llvm.org/) este un compilator open-source de C\C++. Adesea este folosit în IDE-uri datorită mesajelor de eroare de compilare foarte sugestive pe care le produce.

>**NOTE**: `icc` este compilatorul de C\C++ al celor de la compania Intel.


Scrieți în zona Code editor următoarea secvență de cod:
```C
int simple_fn(void)
{
    int a = 1;
    a++;
    return a;
}
```
Observați codul în limbaj de asamblare atunci când opțiunile de compilare (`Compiler options`) sunt `-m32`, respectiv atunci când opțiunile de compilare sunt `-m32 -O2`. Observați ce efect au opțiunile de optimizare asupra codului în limbaj de asamblare generat.


### 2. C: Warm-up GOTOs

Intrați în directorul `2-warm-up-gotos`.<br>

**2.1** Modificați codul sursă din fișierul `bogosort.c` ([Bogosort](https://en.wikipedia.org/wiki/Bogosort)) prin înlocuirea instrucțiunii break cu o instrucțiune goto astfel încât funcționalitatea să se păstreze.

**2.2** În mod asemănător modificați instrucțiunea continue din ignore_the_comments.c astfel încât funcționalitatea codului să se păstreze.


>**WARNING**: Când scrieți cod cu etichete (label-uri) țineți cont de următoarele recomandări de indentare:
- Nu indentați etichetele (label-urile). “Lipiți-le” de marginea din stânga a ecranului de editare.
- O etichetă este singură pe linie. Nu există cod după etichetă.
- Nu țineți cont de etichete în indetarea codului. Codul trebuie indendat în același mod și cu etichete și fără etichete.
- Puneți o linie liberă înaintea liniei care conține o etichetă.


>**NOTE**: [Caz](https://stackoverflow.com/questions/3517726/what-is-wrong-with-using-goto/3517765#3517765) în care goto poate fi util

### 3. C: GOTOs

Intrați în directorul `3-goto-algs`.<br>

Pentru algoritmii de mai jos scrieți cod în C fără a folosi:

- definiții / apeluri de funcţii (exceptând scanf() şi printf())
- else
- for
- while
- do {} while;
- construcțiile if care conțin return
- if-uri imbricate

Singura instrucțiune permisă în cadrul unui if este `goto`.

În alte cuvinte, tot codul trebuie să fie scris în interiorul funcției main, iar modificarea fluxului de control (saltul la altă zonă de cod) se face doar prin intermediul secvențelor de tipul if (conditie) goto eticheta; sau goto eticheta;.

**3.1** Implementați maximul dintr-un vector folosind cod C și constrângerile de mai sus.

**3.2** Implementați căutare binară folosind cod C și constrângerile de mai sus.

>**WARNING**: Reiterăm ideea că scenariile de utilizare ale instrucțiunii goto sunt limitate. Exercițiile acestea au valoare didactică pentru a vă acomoda cu instrucțiuni de salt (jump) pe care le vom folosi în dezvoltarea în limbaj de asamblare.

### 4. Tutorial Ghidra: Decompilare

Intrați în directorul `4-tutorial-ghidra`.<br>

În cadrul acestui exercițiu dorim să analizăm funcționalitatea unui binar simplu, care cere introducerea unei parole corecte pentru obținerea unei valori secrete.

>**WARNING**: Pentru a rula Ghidra, intrați într-o fereastră de terminal și utilizați comanda `ghidra`.

Pentru început, când rulăm Ghidra ne va apărea o fereastră cu proiectele noastre curente.

![ghidra-initial.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/ghidra-initial.png?cache=)

Putem să creăm un nou proiect și să îi dăm un nume corespunzător. Pentru asta vom folosi: `File → New Project` (sau folosind combinația de taste `CTRL + N`).

![ghidra-added-project.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/ghidra-added-project.png?cache=)

După ce am creat proiectul, ca să adăugăm fisierul executabil putem să folosim `File → Import file`, sau să tragem fișierul în directorul pe care l-am creat. Ghidra ne va sugera formatul pe care l-a detectat, precum și compilatorul folosit, în cazuri mai speciale probabil va trebui să schimbăm aceste configurări, dar pentru scopul acestui tutorial, ce ne sugerează Ghidra este perfect.

![ghidra-added-file.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/ghidra-added-file.png?cache=)

Următorul pas este să analizăm binarul pe care l-am importat. Putem să apăsăm dublu click pe acesta. Ghidra ne va întreba daca vrem să îl analizăm. Pentru a face acest lucru, vom apăsa `Yes` și apoi `Analyze`.

![ghidra-analyzed.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/ghidra-analyzed.png?cache=)

Dupa ce executabilul a fost analizat, Ghidra afișează o interpretare a informațiilor binare, care include și codul dezasamblat al programului. În continuare, putem de exemplu să încercam să decompilăm o funcție. În partea stângă a ferestrei avem secțiunea `Symbol Tree`; dacă deschidem `Functions`, putem observa că Ghidra ne-a detectat anumite funcții, chiar și funcmain-ul în cazul acestui binar. Astfel dacă dăm dublu click pe main, ne apare în dreapta funcția main decompilată și în fereastra centrală codul în limbajul de asamblare aferent.

![ghidra-main.png](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/ghidra-main.png?cache=)

Putem să observăm acum că decompilarea nu este tocmai 1:1 cu codul sursă (din fișierul `crackme.c`), dar ne da o idee destul de bună a acestuia. Urmărind codul decompilat, observăm că funcția main are doi parametri de tip long, care se numesc `param_1` și `param_2`, în loc de prototipul normal `main(int argc, char *argv[])`. Al doilea parametru al main-ului este de tip “vector de pointeri către date de tip caracter” (care este interpretat în mod generic ca “vector de șiruri de caractere”). Mai jos este o perspectivă generică asupra modului de reprezentare al vectorului pentru un sistem de 64 de biți. În reprezentarea de pe a doua linie, interpretați `argp` ca fiind `char *argp = (char *)argv`, pentru a avea sens calculul `argp + N`.

| argv[0]  |      argv[1]  |  argv[2]  |
|----------|:-------------:|----------:|
|   argp   |    argp + 8   | argp + 16 |


Diferența de tip a parametrilor main-ului este una legată de interpretare: binarul este compilat pentru arhitectura amd64 (care este extensia arhitecturii x86 pentru 64 de biți), iar dimensiunea unui [cuvânt de procesor](https://en.wikipedia.org/wiki/Word_(computer_architecture)) este de 8 octeți (sau 64 de biți). Dimensiunea unui cuvânt de procesor se reflectă în dimensiunea unui pointer, dar și în dimensiunea unui parametru unic (dacă parametrul este mai mic de un cuvânt, se face automat extensia până la dimensiunea unui cuvânt). Totodată, printr-o coincidență, dimensiunea unei variabile de tip `long` este tot de 64 de biți (dimensiunile [tipurilor de date](https://en.wikipedia.org/wiki/C_data_types) în C nu sunt bine stabilite, fiind definite doar niște limite inferioare pentru date). Acest lucru face ca interpretarea celor doi parametri să fie ca `long`, deoarece toți parametrii, indiferent de tip (int sau pointer) se manipulează identic. Calculul `param_2 + 8` este folosit pentru a calcula adresa celui de-al doilea pointer din vectorul `argv` (adică `argv[1]`). Pentru un program compilat pentru arhitectura x86 de 32 de biți, adresa lui `argv[1]` ar fi fost `param_2 + 4`.

Folosind informațiile din codul decompilat putem să ne dăm seama că programul așteaptă o parolă ca argument și aceasta trebuie să fie din 8 caractere și caracterul de pe poziția 3 trebuie să fie 'E'. Deci putem să îi punem ca input o parolă de genul “AAAEAAAA”.

### 5. Reverse: Old hits

Intrați în directorul `5-old-hits`.<br>

Folosind informațiile noi dobândite despre Ghidra, dar și cele învățate anterior despre folosirea gdb, analizați binarul și obțineți informația secretă.
Programul generează o valoare aleatoare și vă cere să ghiciți o altă valoare calculată pe baza valorii aleatoare.<br>

Mult succes!

## Soluții

Soluțiile pentru exerciții sunt disponibile [aici](https://elf.cs.pub.ro/asm/res/laboratoare/lab-03-sol.zip).  -->