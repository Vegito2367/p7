.data 
.align 8
.section .note.GNU-stack,"",@progbits
.globl main
.text
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
movq $5, %rdi
callq printInt
lbl_1: addq $0, %rsp
popq %rbp
retq
main: callq fun_main
movq $60, %rax
movq $7, %rdi
syscall
