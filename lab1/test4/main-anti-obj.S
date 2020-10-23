
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	48 83 ec 18          	sub    $0x18,%rsp
   4:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
   b:	00 00 
   d:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  12:	31 c0                	xor    %eax,%eax
  14:	48 8d 74 24 04       	lea    0x4(%rsp),%rsi
  19:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 20 <main+0x20>
  20:	e8 00 00 00 00       	callq  25 <main+0x25>
  25:	8b 54 24 04          	mov    0x4(%rsp),%edx
  29:	83 fa 01             	cmp    $0x1,%edx
  2c:	7e 3f                	jle    6d <main+0x6d>
  2e:	be 01 00 00 00       	mov    $0x1,%esi
  33:	b8 02 00 00 00       	mov    $0x2,%eax
  38:	0f af f0             	imul   %eax,%esi
  3b:	83 c0 01             	add    $0x1,%eax
  3e:	39 d0                	cmp    %edx,%eax
  40:	7e f6                	jle    38 <main+0x38>
  42:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 49 <main+0x49>
  49:	b8 00 00 00 00       	mov    $0x0,%eax
  4e:	e8 00 00 00 00       	callq  53 <main+0x53>
  53:	b8 00 00 00 00       	mov    $0x0,%eax
  58:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  5d:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  64:	00 00 
  66:	75 0c                	jne    74 <main+0x74>
  68:	48 83 c4 18          	add    $0x18,%rsp
  6c:	c3                   	retq   
  6d:	be 01 00 00 00       	mov    $0x1,%esi
  72:	eb ce                	jmp    42 <main+0x42>
  74:	e8 00 00 00 00       	callq  79 <.LC1+0x76>
