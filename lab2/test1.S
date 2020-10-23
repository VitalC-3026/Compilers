    .text
    .global n
    .bss
    .align  4
    .type   n, @object
    .size   n, 4

n:
    .zero   4

    .text
    .globl  factorial
    .type   factorial, @function

factorial:
    movl    $2, %ecx
    movl    $1, %edx
    jmp     .L2

.L3:
    imull   %ecx, %edx
    addl    $1, %ecx

.L2:
    cmpl    %eax, %ecx 
    jle .L3
    movl    %edx, %eax
    ret

    .section    .rodata

STR0:
    .string "%d"

STR1:
    .string "factorial is: %d\n"

    .text
    .globl  main
    .type   main, @function

main:
    pushl   $n
    pushl   $STR0
    call    scanf
    addl    $8, %esp
    movl    n, %eax
    pushl   %eax
    call    factorial
    addl    $4, %esp
    pushl   %eax
    pushl   $STR1
    call    printf
    addl    $8, %esp
    movl $0, %eax
    ret


    .section    .note.GNU-stack,"",@progbits

