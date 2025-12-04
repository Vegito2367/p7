.data 
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
callq fun_main
#Fn epilogue <init>
lbl_0: addq $0, %rsp
popq %rbp
retq
fun_f1: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $32, %rsp
#Fn body f1
movq $1, %rax
movq %rax, -24(%rbp)
movq $0, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rax
movq -40(%rbp), %rax
jmp lbl_1
#Fn epilogue f1
lbl_1: addq $32, %rsp
popq %rbp
retq
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $96, %rsp
#Fn body main
movq $1, %rax
movq %rax, -32(%rbp)
movq $0, %rax
movq %rax, -24(%rbp)
movq $1, %rax
movq %rax, -40(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -80(%rbp)
movq -80(%rbp), %rax
movq %rax, -48(%rbp)
movq -24(%rbp), %rax
movq -40(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -88(%rbp)
movq -88(%rbp), %rax
movq %rax, -56(%rbp)
movq -48(%rbp), %rax
movq -56(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -96(%rbp)
movq -96(%rbp), %rax
movq %rax, -64(%rbp)
callq fun_f1
movq %rax, -104(%rbp)
movq -64(%rbp), %rax
movq -104(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -112(%rbp)
movq -112(%rbp), %rax
movq %rax, -72(%rbp)
movq -48(%rbp), %rdi
callq printBool
movq $str_0, %rdi
callq printString
movq -56(%rbp), %rdi
callq printBool
movq $str_1, %rdi
callq printString
movq -64(%rbp), %rdi
callq printBool
movq $str_2, %rdi
callq printString
movq -72(%rbp), %rdi
callq printBool
#Fn epilogue main
lbl_2: addq $96, %rsp
popq %rbp
retq
movq $60, %rax
movq $0, %rdi
syscall
