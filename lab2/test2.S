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
    movl    4(%esp), %eax
    addl    $1, %eax
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
    movl    4(%esp), %ecx
    addl    $8, %esp
    pushl   %ecx
    pushl   $STR1
    call    printf
    addl    $8, %esp
    movl $0, %eax
    ret


    .section    .note.GNU-stack,"",@progbits

