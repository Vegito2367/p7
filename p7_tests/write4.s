.data 
global_b: .quad 0
str_3: .asciz "\n"
str_2: .asciz "\n"
str_1: .asciz "\n"
str_0: .asciz "\n"
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
subq $64, %rsp
#Fn body main
movq $8, %rax
movq %rax, -24(%rbp)
movq $2, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cqto
idivq %rbx
movq %rax, -48(%rbp)
movq -48(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printInt
movq $str_0, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
imulq %rbx, %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printInt
movq $str_1, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -64(%rbp)
movq -64(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printInt
movq $str_2, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
subq %rbx, %rax
movq %rax, -72(%rbp)
movq -72(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printInt
movq $str_3, %rdi
callq printString
#Fn epilogue main
lbl_1: addq $64, %rsp
popq %rbp
retq
movq $60, %rax
movq $7, %rdi
syscall
