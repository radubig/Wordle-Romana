.data
    ERR_MSG_1: .asciz "A aparut o eroare la deschiderea fisierului "
    ERR_MSG_2: .asciz "\n"

    rip: .space 4
.text

# Description:
#    Opens a file.
# Usage:
#    pushl *[file_name]
#    call _open
#    popl [file_descriptor]
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

    cmpl $0, %eax # catch error
    jge _open__if_ERR
        pushl %ebx
        pushl $ERR_MSG_1
        call _stderr
        call _stderr
        pushl $ERR_MSG_2
        call _stderr
        
        call _exit
    _open__if_ERR:

    popl %edx # rip
    pushl %eax # file_descriptor
    pushl %edx
    ret
