.data 
global_g: .quad 0
str_7: .asciz "\n"
str_4: .asciz "\n"
str_6: .asciz "Read test:\n"
str_3: .asciz "\n"
str_2: .asciz "\n"
str_1: .asciz "\n"
str_5: .asciz "\n"
str_0: .asciz "\n"
.align 8
.section .note.GNU-stack,"",@progbits
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
#Fn body <init>
movq $5, %rax
movq %rax, global_g
callq fun_main
#Fn epilogue <init>
lbl_0: addq $0, %rsp
popq %rbp
retq
fun_sum8: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $128, %rsp
#Fn body sum8
movq %rdi, -88(%rbp)
movq %rsi, -96(%rbp)
movq %rdx, -104(%rbp)
movq %rcx, -112(%rbp)
movq %r8, -120(%rbp)
movq %r9, -128(%rbp)
movq 8(%rbp), %rbx
movq %rbx, -136(%rbp)
movq 0(%rbp), %rbx
movq %rbx, -144(%rbp)
movq -88(%rbp), %rax
movq -96(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rax
movq -104(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rax
movq -112(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -48(%rbp)
movq -48(%rbp), %rax
movq -120(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -56(%rbp)
movq -56(%rbp), %rax
movq -128(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -64(%rbp)
movq -64(%rbp), %rax
movq -136(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -72(%rbp)
movq -72(%rbp), %rax
movq -144(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -80(%rbp)
movq -80(%rbp), %rax
movq %rax, -24(%rbp)
movq -24(%rbp), %rax
movq -24(%rbp), %rax
jmp lbl_1
#Fn epilogue sum8
lbl_1: addq $128, %rsp
popq %rbp
retq
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $112, %rsp
#Fn body main
movq $10, %rax
movq %rax, -24(%rbp)
movq -24(%rbp), %rax
movq $2, %rbx
imulq %rbx, %rax
movq %rax, -80(%rbp)
movq -80(%rbp), %rax
movq global_g, %rbx
addq %rax, %rbx
movq %rbx, -88(%rbp)
movq -88(%rbp), %rax
movq %rax, -32(%rbp)
movq -32(%rbp), %rax
movq %rax, -72(%rbp)
movq -72(%rbp), %rdi
callq printInt
movq $str_0, %rdi
callq printString
movq $1, %rdi
movq $2, %rsi
movq $3, %rdx
movq $4, %rcx
movq $5, %r8
movq $6, %r9
movq $7, %rax
pushq %rax
movq $8, %rax
pushq %rax
callq fun_sum8
addq $16, %rsp
movq %rax, -96(%rbp)
movq -96(%rbp), %rax
movq %rax, -64(%rbp)
movq -64(%rbp), %rdi
callq printInt
movq $str_1, %rdi
callq printString
movq $1, %rax
movq %rax, -40(%rbp)
movq $0, %rax
movq %rax, -48(%rbp)
movq -40(%rbp), %rax
movq -48(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -104(%rbp)
movq -104(%rbp), %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rdi
callq printBool
movq $str_2, %rdi
callq printString
movq -48(%rbp), %rax
cmpq $0, %rax
movq $0, %rax
sete %al
movq %rax, -112(%rbp)
movq -112(%rbp), %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rdi
callq printBool
movq $str_3, %rdi
callq printString
movq -40(%rbp), %rax
movq -48(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -120(%rbp)
movq -120(%rbp), %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rdi
callq printBool
movq $str_4, %rdi
callq printString
movq -40(%rbp), %rax
movq -48(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -128(%rbp)
movq -128(%rbp), %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rdi
callq printBool
movq $str_5, %rdi
callq printString
movq $str_6, %rdi
callq printString
callq getInt
movq %rax, -24(%rbp)
movq -24(%rbp), %rdi
callq printInt
movq $str_7, %rdi
callq printString
#Fn epilogue main
lbl_2: addq $112, %rsp
popq %rbp
retq
movq $60, %rax
movq $0, %rdi
syscall
