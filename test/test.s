	.file	"test.cpp"
	.text
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	2
	.globl	b
	.bss
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.globl	c
	.data
	.type	c, @object
	.size	c, 1
c:
	.byte	50
	.section	.rodata
	.type	_ZL1j, @object
	.size	_ZL1j, 1
_ZL1j:
	.byte	53
	.globl	d
	.bss
	.type	d, @object
	.size	d, 1
d:
	.zero	1
	.globl	e
	.type	e, @object
	.size	e, 1
e:
	.zero	1
	.globl	f
	.type	f, @object
	.size	f, 1
f:
	.zero	1
	.section	.rodata
	.align 4
	.type	_ZL1i, @object
	.size	_ZL1i, 4
_ZL1i:
	.long	3
	.text
	.globl	_Z3funv
	.type	_Z3funv, @function
_Z3funv:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$2, -4(%ebp)
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z3funv, .-_Z3funv
	.globl	k
	.bss
	.align 4
	.type	k, @object
	.size	k, 4
k:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.cx
	addl	$_GLOBAL_OFFSET_TABLE_, %ecx
	movzbl	c@GOTOFF(%ecx), %eax
	movsbl	%al, %edx
	movl	a@GOTOFF(%ecx), %eax
	imull	%edx, %eax
	movl	%eax, b@GOTOFF(%ecx)
	movl	$4, -8(%ebp)
	movl	a@GOTOFF(%ecx), %ebx
	movl	-8(%ebp), %eax
	cltd
	idivl	%ebx
	movl	%eax, b@GOTOFF(%ecx)
	movl	$0, %eax
	addl	$16, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB2:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE2:
	.section	.text.__x86.get_pc_thunk.cx,"axG",@progbits,__x86.get_pc_thunk.cx,comdat
	.globl	__x86.get_pc_thunk.cx
	.hidden	__x86.get_pc_thunk.cx
	.type	__x86.get_pc_thunk.cx, @function
__x86.get_pc_thunk.cx:
.LFB3:
	.cfi_startproc
	movl	(%esp), %ecx
	ret
	.cfi_endproc
.LFE3:
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
