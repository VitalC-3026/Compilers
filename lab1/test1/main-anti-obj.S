
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <max>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	89 7d fc             	mov    %edi,-0x4(%rbp)
   7:	89 75 f8             	mov    %esi,-0x8(%rbp)
   a:	8b 45 fc             	mov    -0x4(%rbp),%eax
   d:	3b 45 f8             	cmp    -0x8(%rbp),%eax
  10:	7c 05                	jl     17 <max+0x17>
  12:	8b 45 fc             	mov    -0x4(%rbp),%eax
  15:	eb 03                	jmp    1a <max+0x1a>
  17:	8b 45 f8             	mov    -0x8(%rbp),%eax
  1a:	5d                   	pop    %rbp
  1b:	c3                   	retq   

000000000000001c <main>:
  1c:	55                   	push   %rbp
  1d:	48 89 e5             	mov    %rsp,%rbp
  20:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 27 <main+0xb>
  27:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 2e <main+0x12>
  2e:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 35 <main+0x19>
  35:	b8 00 00 00 00       	mov    $0x0,%eax
  3a:	e8 00 00 00 00       	callq  3f <main+0x23>
  3f:	8b 15 00 00 00 00    	mov    0x0(%rip),%edx        # 45 <main+0x29>
  45:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 4b <main+0x2f>
  4b:	89 d6                	mov    %edx,%esi
  4d:	89 c7                	mov    %eax,%edi
  4f:	e8 00 00 00 00       	callq  54 <main+0x38>
  54:	89 c6                	mov    %eax,%esi
  56:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 5d <main+0x41>
  5d:	b8 00 00 00 00       	mov    $0x0,%eax
  62:	e8 00 00 00 00       	callq  67 <main+0x4b>
  67:	b8 00 00 00 00       	mov    $0x0,%eax
  6c:	5d                   	pop    %rbp
  6d:	c3                   	retq   
