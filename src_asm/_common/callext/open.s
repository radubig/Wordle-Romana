.text
.extern _exit
.extern _stderr

# Wrapper around open syscall
# Usage:
#    pushl [file_name]
#    call _open
#    popl [file_descriptor]

.data
    ERR_ACCESS: .asciz "Nu s-a putut accesa fisierul "
    
    ERR_GENERIC_1: .asciz "A aparut o eroare la deschiderea fisierului "
    ERR_GENERIC_2: .asciz "\nCod de eroare: "
    
    ERR_INVALID_0: .asciz "Numele fisierului "
    ERR_INVALID_1: .asciz " este invalid"
    
    ERR_MISSING_0: .asciz "Fisierul "
    ERR_MISSING_1: .asciz " nu exista"
    
    err_generic_display: .space 8
.text

.global _open
_open:
    popl %edx # rip
    popl %ebx # filename
    pushl %edx

    movl $5, %eax # syscall 5: open
    # %ebx (file_name) is popped from stack
    movl $0, %ecx # O_RDONLY (read only)
    movl $0, %edx # ignored for O_RDONLY
    int $0x80

    cmpl $0, %eax
    jge _open__if_ERR_GENERIC
        movl %eax, err_generic_display
        pushl $err_generic_display
        pushl $ERR_GENERIC_2
        pushl %ebx
        pushl $ERR_GENERIC_1
        call _stderr
        call _stderr
        call _stderr
        call _stderr
        
        call _exit
    _open__if_ERR_GENERIC:

    cmpl $0xfffffffe, %eax # error code 2: ENOENT
    jne _open__if_ERR_MISSING
        pushl $ERR_MISSING_1
        pushl %ebx
        pushl $ERR_MISSING_0
        call _stderr
        call _stderr
        call _stderr
        
        call _exit
    _open__if_ERR_MISSING:

    cmpl $0xfffffff3, %eax # error code 13: EACCES
    jne _open__if_ERR_ACCESS
        pushl %ebx
        pushl $ERR_ACCESS
        call _stderr
        call _stderr
        
        call _exit
    _open__if_ERR_ACCESS:
    
    cmpl $0xffffffea, %eax # error code 22: EINVAL
    je _open__if_ERR_INVALID
    cmpl $0xffffffec, %eax # error code 20: ENOTDIR
    je _open__if_ERR_INVALID
    jmp _open__if_ERR_INVALID_end
    _open__if_ERR_INVALID:
        pushl $ERR_INVALID_1
        pushl %ebx
        pushl $ERR_INVALID_0
        call _stderr
        call _stderr
        call _stderr
        
        call _exit
    _open__if_ERR_INVALID_end:

    popl %edx # rip
    pushl %eax # file_descriptor
    pushl %edx
    ret
