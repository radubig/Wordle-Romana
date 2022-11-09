# Wrapper around read syscall
# Usage:
#    pushl [file_descriptor]
#    pushl [buffer]
#    pushl [length]
#    call _read

.data
    ERR_MSG_1: .asciz "A aparut o eroare la citirea din fisierul "
    ERR_MSG_2: .asciz "\n"

.text

.global _read
_read:
    popl %eax # rip
    popl %edx # length
    popl %ecx # buffer
    popl %ebx # fide_descriptor
    pushl %eax

    movl $3, %eax # syscall 3: read
    # %ebx (file_descriptor) is popped from stack
    # %ecx (buffer) is popped from stack
    # %edx (length) is popped from stack
    int $0x80
    
    cmpl $0, %eax # catch error
    jge _read__if_ERR
        pushl %ebx
        pushl $ERR_MSG_1
        call _stderr
        call _stderr
        pushl $ERR_MSG_2
        call _stderr
        
        call _exit
    _read__if_ERR:
    
    ret
