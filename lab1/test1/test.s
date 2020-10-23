	.file	"main.c"
	.text
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.text
	.globl	max
	.type	max, @function
max:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	.L2
	movl	8(%ebp), %eax
	jmp	.L3
.L2:
	movl	12(%ebp), %eax
.L3:
	popl	%ebp
	ret
	.size	max, .-max
	.section	.rodata
.LC0:
	.string	"%d, %d"
.LC1:
	.string	"max is: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$4, %esp
	subl	$4, %esp
	pushl	$b
	pushl	$a
	pushl	$.LC0
	call	__isoc99_scanf
	addl	$16, %esp
	movl	b, %edx
	movl	a, %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	max
	addl	$16, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
