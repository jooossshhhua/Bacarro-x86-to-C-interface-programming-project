section .text
bits 64
default rel

global daxpy_asm

daxpy_asm:

    push rbp 
    mov rbp, rsp
    add rbp, 16
    mov r10, [rbp+32] 

    sub rcx, 1 ; n counter
    
    start_loop:

        cmp rcx, 0
        jl end_loop

        movsd xmm2, [r8 + rcx*8]  ;load xi
        movsd xmm3, [r9 + rcx*8]  ;load yi

        mulsd xmm2, xmm1 
        addsd xmm2, xmm3 
        movsd [r10 + rcx*8], xmm2 ; load zi

        dec rcx 

        jmp start_loop 

end_loop:
    pop rbp
    ret