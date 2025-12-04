.data 
str_31: .asciz "\n"
str_30: .asciz "\n"
str_29: .asciz "\n"
str_12: .asciz "\n"
str_2: .asciz "\n"
str_27: .asciz "\n"
str_24: .asciz "\n"
str_8: .asciz "\n"
str_22: .asciz "\n"
str_21: .asciz "\n"
str_5: .asciz "\n"
str_20: .asciz "\n"
str_4: .asciz "\n"
str_19: .asciz "\n"
str_3: .asciz "\n"
str_18: .asciz "\n"
str_11: .asciz "\n"
str_1: .asciz "\n"
str_26: .asciz "\n"
str_25: .asciz "\n"
str_0: .asciz "\n"
str_13: .asciz "\n"
str_28: .asciz "\n"
str_9: .asciz "\n"
str_14: .asciz "\n"
str_10: .asciz "\n"
str_15: .asciz "\n"
str_6: .asciz "\n"
str_16: .asciz "\n"
str_7: .asciz "\n"
str_17: .asciz "\n"
str_23: .asciz "\n"
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
fun_main: pushq %rbp
movq %rsp, %rbp
addq $16,%rbp
subq $800, %rsp
#Fn body main
movq $1, %rax
movq %rax, -24(%rbp)
movq $1, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -48(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -56(%rbp)
movq -48(%rbp), %rax
movq -56(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -64(%rbp)
movq -64(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_0, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -72(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -80(%rbp)
movq -72(%rbp), %rax
movq -80(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -88(%rbp)
movq -88(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_1, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -96(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -104(%rbp)
movq -96(%rbp), %rax
movq -104(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -112(%rbp)
movq -112(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_2, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -120(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -128(%rbp)
movq -120(%rbp), %rax
movq -128(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -136(%rbp)
movq -136(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_3, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -144(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -152(%rbp)
movq -144(%rbp), %rax
movq -152(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -160(%rbp)
movq -160(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_4, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -168(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -176(%rbp)
movq -168(%rbp), %rax
movq -176(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -184(%rbp)
movq -184(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_5, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -192(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -200(%rbp)
movq -192(%rbp), %rax
movq -200(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -208(%rbp)
movq -208(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_6, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -216(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -224(%rbp)
movq -216(%rbp), %rax
movq -224(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -232(%rbp)
movq -232(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_7, %rdi
callq printString
movq $1, %rax
movq %rax, -24(%rbp)
movq $0, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -240(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -248(%rbp)
movq -240(%rbp), %rax
movq -248(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -256(%rbp)
movq -256(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_8, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -264(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -272(%rbp)
movq -264(%rbp), %rax
movq -272(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -280(%rbp)
movq -280(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_9, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -288(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -296(%rbp)
movq -288(%rbp), %rax
movq -296(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -304(%rbp)
movq -304(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_10, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -312(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -320(%rbp)
movq -312(%rbp), %rax
movq -320(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -328(%rbp)
movq -328(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_11, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -336(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -344(%rbp)
movq -336(%rbp), %rax
movq -344(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -352(%rbp)
movq -352(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_12, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -360(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -368(%rbp)
movq -360(%rbp), %rax
movq -368(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -376(%rbp)
movq -376(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_13, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -384(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -392(%rbp)
movq -384(%rbp), %rax
movq -392(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -400(%rbp)
movq -400(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_14, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -408(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -416(%rbp)
movq -408(%rbp), %rax
movq -416(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -424(%rbp)
movq -424(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_15, %rdi
callq printString
movq $0, %rax
movq %rax, -24(%rbp)
movq $0, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -432(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -440(%rbp)
movq -432(%rbp), %rax
movq -440(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -448(%rbp)
movq -448(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_16, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -456(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -464(%rbp)
movq -456(%rbp), %rax
movq -464(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -472(%rbp)
movq -472(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_17, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -480(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -488(%rbp)
movq -480(%rbp), %rax
movq -488(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -496(%rbp)
movq -496(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_18, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -504(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -512(%rbp)
movq -504(%rbp), %rax
movq -512(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -520(%rbp)
movq -520(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_19, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -528(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -536(%rbp)
movq -528(%rbp), %rax
movq -536(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -544(%rbp)
movq -544(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_20, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -552(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -560(%rbp)
movq -552(%rbp), %rax
movq -560(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -568(%rbp)
movq -568(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_21, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -576(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -584(%rbp)
movq -576(%rbp), %rax
movq -584(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -592(%rbp)
movq -592(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_22, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -600(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -608(%rbp)
movq -600(%rbp), %rax
movq -608(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -616(%rbp)
movq -616(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_23, %rdi
callq printString
movq $0, %rax
movq %rax, -24(%rbp)
movq $1, %rax
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -624(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -632(%rbp)
movq -624(%rbp), %rax
movq -632(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -640(%rbp)
movq -640(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_24, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -648(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -656(%rbp)
movq -648(%rbp), %rax
movq -656(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -664(%rbp)
movq -664(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_25, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -672(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -680(%rbp)
movq -672(%rbp), %rax
movq -680(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -688(%rbp)
movq -688(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_26, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -696(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -704(%rbp)
movq -696(%rbp), %rax
movq -704(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -712(%rbp)
movq -712(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_27, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -720(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -728(%rbp)
movq -720(%rbp), %rax
movq -728(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -736(%rbp)
movq -736(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_28, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -744(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -752(%rbp)
movq -744(%rbp), %rax
movq -752(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -760(%rbp)
movq -760(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_29, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -768(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
sete %al
movq %rax, -776(%rbp)
movq -768(%rbp), %rax
movq -776(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -784(%rbp)
movq -784(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_30, %rdi
callq printString
movq -24(%rbp), %rax
movq -32(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -792(%rbp)
movq -32(%rbp), %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rax
setne %al
movq %rax, -800(%rbp)
movq -792(%rbp), %rax
movq -800(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -808(%rbp)
movq -808(%rbp), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
callq printBool
movq $str_31, %rdi
callq printString
#Fn epilogue main
lbl_1: addq $800, %rsp
popq %rbp
retq
movq $60, %rax
movq $0, %rdi
syscall
