.data 
global_b: .quad 0
.align 8
.section .note.GNU-stack,"",@progbits
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
#Fn body <init>
movq $17, %rax
movq %rax, global_b
callq fun_main
#Fn epilogue <init>
lbl_0: addq $0, %rsp
popq %rbp
retq
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $32, %rsp
#Fn body main
movq $4, %rax
movq %rax, -24(%rbp)
movq -24(%rbp), %rax
movq $5, %rbx
addq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rax
movq %rax, -32(%rbp)
movq global_b, %rax
movq -24(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -48(%rbp)
movq -48(%rbp), %rax
movq %rax, global_b
movq global_b, %rdi
callq printInt
#Fn epilogue main
lbl_1: addq $32, %rsp
popq %rbp
retq
movq $60, %rax
movq $7, %rdi
syscall
