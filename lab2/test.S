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
    subl    $8, %esp
    movl    $2, 4(%esp)
    movl    $1, 0(%esp)
    jmp     .L2

.L3:
    movl    0(%esp), %ecx
    imull   4(%esp), %ecx
    movl    %ecx, 0(%esp)
    addl    $1, 4(%esp)

.L2:
    cmpl    %eax, 4(%esp) 
    jle .L3
    movl    0(%esp), %eax
    addl    $8, %esp
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
    pushl   n
    call    factorial
    addl    $4, %esp
    pushl   %eax
    pushl   $STR1
    call    printf
    addl    $8, %esp
    movl $0, %eax
    ret


    .section    .note.GNU-stack,"",@progbits

