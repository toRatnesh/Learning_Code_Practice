## Comparison of string_view and string

This assembly is generated with -O2 and gcc 10.2

* M-1

length(std::basic_string_view<char, std::char_traits<char> >):
        mov     rax, rdi
        ret
main:
        sub     rsp, 24
        mov     esi, 23
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<unsigned long>(unsigned long)
        lea     rsi, [rsp+15]
        mov     edx, 1
        mov     BYTE PTR [rsp+15], 10
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
        xor     eax, eax
        add     rsp, 24
        ret
_GLOBAL__sub_I_length(std::basic_string_view<char, std::char_traits<char> >):
        sub     rsp, 8
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        add     rsp, 8
        jmp     __cxa_atexit
		
		
* M-2

length(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&):
        mov     rax, QWORD PTR [rdi+8]
        ret
main:
        push    rbp
        xor     edx, edx
        sub     rsp, 48
        lea     rax, [rsp+32]
        lea     rsi, [rsp+8]
        mov     QWORD PTR [rsp+8], 23
        lea     rdi, [rsp+16]
        mov     QWORD PTR [rsp+16], rax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_create(unsigned long&, unsigned long)
        mov     rdx, QWORD PTR [rsp+8]
        mov     edi, OFFSET FLAT:_ZSt4cout
        movdqa  xmm0, XMMWORD PTR .LC0[rip]
        mov     QWORD PTR [rsp+16], rax
        mov     QWORD PTR [rsp+32], rdx
        mov     edx, 28265
        movups  XMMWORD PTR [rax], xmm0
        mov     WORD PTR [rax+20], dx
        mov     rdx, QWORD PTR [rsp+16]
        mov     DWORD PTR [rax+16], 1920234272
        mov     BYTE PTR [rax+22], 103
        mov     rax, QWORD PTR [rsp+8]
        mov     QWORD PTR [rsp+24], rax
        mov     BYTE PTR [rdx+rax], 0
        mov     rsi, QWORD PTR [rsp+24]
        call    std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<unsigned long>(unsigned long)
        mov     rdi, rax
        mov     edx, 1
        lea     rsi, [rsp+8]
        mov     BYTE PTR [rsp+8], 10
        call    std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
        lea     rdi, [rsp+16]
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        add     rsp, 48
        xor     eax, eax
        pop     rbp
        ret
        mov     rbp, rax
        jmp     .L4
main.cold:
.L4:
        lea     rdi, [rsp+16]
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        mov     rdi, rbp
        call    _Unwind_Resume
_GLOBAL__sub_I_length(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&):
        sub     rsp, 8
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        add     rsp, 8
        jmp     __cxa_atexit
.LC0:
        .quad   2338328219631577172
        .quad   7308339910404153441
		

