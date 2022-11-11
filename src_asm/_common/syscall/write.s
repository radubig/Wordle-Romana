.data
    ERR_MSG_1: .asciz "A aparut o eroare la citirea din fisierul "
    ERR_MSG_2: .asciz "\n"

.text

# Description
#    Writes data to a file descriptor.
# Usage:
#    pushl *[data]
#    pushl [file_descriptor]
#    call _write
.global _write
_write:
    popl %edx # rip
    popl %ebx # file_descriptor
    popl %ecx # data
    pushl %edx

    movl $4, %eax # syscall 4: write
    # %ebx (file_descriptor) is popped from stack
    # %ecx (data) is popped from stack
    pushl %ecx
    call string__length
    popl %edx # data_len
    int $0x80
    
    cmpl $0, %eax # catch error
    jge _write__if_ERR
        pushl %ebx
        pushl $ERR_MSG_1
        call _stderr
        call _stderr
        pushl $ERR_MSG_2
        call _stderr
        
        call _exit
    _write__if_ERR:
    
    ret

# Description
#    Writes data to stdout.
# Usage:
#    pushl *[data]
#    call _stdout
.global _stdout
_stdout:
    popl %edx # rip
    pushl $1 # stdout
    pushl %edx
    jmp _write

# Description
#    Writes data to stderr.
# Usage:
#    pushl *[data]
#    call _stderr
.global _stderr
_stderr:
    popl %edx # rip
    pushl $2 # stderr
    pushl %edx
    jmp _write
