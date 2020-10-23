    .text
    .globl  max
    .type   max, @function

max:
    movl    4(%esp),    %eax
    cmpl    8(%esp),    %eax
    jl      L2

    movl    4(%esp),    %eax
    jmp     L3

L2:
    movl    8(%esp),    %eax

L3:
    ret

    .bss
    .align  4
a:
    .zero   4
    .align  4

b:
    .zero   4
    .align  4
c:
    .zero   8

    .section    .rodata
STR0:
    .string "%d %d"
STR1:
    .string "max is: %d\n"

    .text
    .globl  main
    .type   main, @function

main:
    pushl   $b
    pushl   $a
    pushl   $STR0
    call    scanf
    addl    $12, %esp
    movl    b, %edx
    movl    a, %eax
    pushl   %edx
    pushl   %eax
    call    max
    addl    $8, %esp
    pushl   %eax
    pushl   $STR1
    call    printf
    addl    $8, %esp
    movl    $0, %eax
    ret
    .section .note.GNU-stack,"",@progbits
