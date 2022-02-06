// CASE - 1 | return 5; | Without Optimization

main:
        push    rbp
        mov     rbp, rsp
        mov     eax, 5
        pop     rbp
        ret

// CASE - 2 | return [](){return 5;}(); | Without Optimization

_ZZ4mainENKUlvE_clEv:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     eax, 5
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        lea     rax, [rbp-1]
        mov     rdi, rax
        call    _ZZ4mainENKUlvE_clEv
        nop
        leave
        ret
		
		
// CASE - 3 | return 5; | With Optimization -O1

main:
        mov     eax, 5
        ret

// CASE - 4 | return [](){return 5;}(); | With Optimization -O1

main:
        mov     eax, 5
        ret

// CASE - 5 | return Lambda()(); | Without Optimization

Lambda::operator()() const:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $5, %eax
        popq    %rbp
        ret
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        leaq    -1(%rbp), %rax
        movq    %rax, %rdi
        call    Lambda::operator()() const
        nop
        leave
        ret

// CASE - 6 | return Lambda()(); | With Optimization -O1

main:
        movl    $5, %eax
        ret



