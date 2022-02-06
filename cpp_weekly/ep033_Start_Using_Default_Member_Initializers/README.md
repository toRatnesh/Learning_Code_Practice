// CASE - 1 | Without Optimization

main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 5
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
		
// CASE - 1 | With Optimization

main:
        mov     eax, 5
        ret

// CASE - 2 | Without Optimization
_ZN1SC2Ei:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     DWORD PTR [rbp-12], esi
        mov     rax, QWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-12]
        mov     DWORD PTR [rax], edx
        nop
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        lea     rax, [rbp-4]
        mov     esi, 5
        mov     rdi, rax
        call    _ZN1SC1Ei
        mov     eax, DWORD PTR [rbp-4]
        leave
        ret
		
// CASE - 2 | With Optimization

main:
        mov     eax, 5
        ret

