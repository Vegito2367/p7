.data 
global_b: .quad 0
str_11: .asciz "\n"
str_10: .asciz "User read value:"
str_8: .asciz "Function return value:"
str_9: .asciz "\n"
str_6: .asciz "Function call ends\n"
str_4: .asciz "\n"
str_3: .asciz "\n"
str_7: .asciz "\n"
str_2: .asciz "End of first part of function test - Now testing stack variables\n"
str_5: .asciz "Function call begins\n"
str_1: .asciz "if condition inside function works!\n"
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
fun_f1: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $96, %rsp
#Fn body f1
movq %rdi, -48(%rbp)
movq %rsi, -56(%rbp)
movq %rdx, -64(%rbp)
movq %rcx, -72(%rbp)
movq %r8, -80(%rbp)
movq %r9, -88(%rbp)
movq 8(%rbp), %rbx
movq %rbx, -96(%rbp)
movq 0(%rbp), %rbx
movq %rbx, -104(%rbp)
movq $7, %rax
movq $2, %rbx
imulq %rbx, %rax
movq %rax, -24(%rbp)
movq -24(%rbp), %rax
movq %rax, -48(%rbp)
movq $2, %rax
movq -64(%rbp), %rbx
imulq %rbx, %rax
movq %rax, -32(%rbp)
movq -48(%rbp), %rax
movq -32(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rax
movq %rax, -56(%rbp)
movq -56(%rbp), %rdi
callq printInt
movq $str_0, %rdi
callq printString
movq -72(%rbp), %rcx
cmpq $0, %rcx
je lbl_2
movq $str_1, %rdi
callq printString
lbl_2: nop
movq $str_2, %rdi
callq printString
movq -96(%rbp), %rdi
callq printInt
movq $str_3, %rdi
callq printString
movq -104(%rbp), %rdi
callq printInt
movq $str_4, %rdi
callq printString
movq -56(%rbp), %rax
movq -56(%rbp), %rax
jmp lbl_1
#Fn epilogue f1
lbl_1: addq $96, %rsp
popq %rbp
retq
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $48, %rsp
#Fn body main
movq $5, %rax
movq %rax, -32(%rbp)
lbl_4: nop
movq -32(%rbp), %rax
movq $10, %rbx
cmpq %rbx, %rax
movq $0, %rax
setl %al
movq %rax, -48(%rbp)
movq -48(%rbp), %rcx
cmpq $0, %rcx
je lbl_5
movq -32(%rbp), %rax
movq $1, %rbx
addq %rax, %rbx
movq %rbx, -32(%rbp)
jmp lbl_4
lbl_5: nop
movq $str_5, %rdi
callq printString
movq -32(%rbp), %rax
movq $0, %rbx
cmpq %rbx, %rax
movq $0, %rax
setg %al
movq %rax, -56(%rbp)
movq -32(%rbp), %rdi
movq $0, %rsi
movq $10, %rdx
movq -56(%rbp), %rcx
movq $0, %r8
movq $1, %r9
movq $25, %rax
pushq %rax
movq $26, %rax
pushq %rax
callq fun_f1
addq $16, %rsp
movq %rax, -64(%rbp)
movq -64(%rbp), %rax
movq %rax, -40(%rbp)
movq $str_6, %rdi
callq printString
movq -32(%rbp), %rdi
callq printInt
movq $str_7, %rdi
callq printString
movq $str_8, %rdi
callq printString
movq -40(%rbp), %rdi
callq printInt
movq $str_9, %rdi
callq printString
callq getInt
movq %rax, -40(%rbp)
movq $str_10, %rdi
callq printString
movq -40(%rbp), %rdi
callq printInt
movq $str_11, %rdi
callq printString
#Fn epilogue main
lbl_3: addq $48, %rsp
popq %rbp
retq
movq $60, %rax
movq $0, %rdi
syscall
