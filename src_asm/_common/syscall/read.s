.data
    ERR_MSG_1: .asciz "A aparut o eroare la citirea din fisierul "
    ERR_MSG_2: .asciz "\n"

.text

# Description
#    Reads data up to the specified length from a file descriptor and returns the actual length of the data.
# Usage:
#    pushl [file_descriptor]
#    pushl *[buffer]
#    pushl [max_length]
#    call _read
#    popl [length]
.global _read
_read:
    popl %eax # rip
    popl %edx # length
    popl %ecx # buffer
    popl %ebx # file_descriptor
    pushl %eax

    movl $3, %eax # syscall 3: read
    # %ebx (file_descriptor) is popped from stack
    # %ecx (buffer) is popped from stack
    # %edx (max_length) is popped from stack
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
    
    popl %edx # rip
    pushl %eax # length
    pushl %edx
    
    ret

# Description
#    Reads data up to the specified length from stdin and returns the actual length of the data.
# Usage:
#     pushl *[buffer]
#     pushl [max_length]
#     call _stdin
#     popl [length]
.global _stdin
_stdin:
    popl %edx # rip
    popl %ecx # max_length
    popl %eax # buffer
    pushl $0 # stdin
    pushl %eax
    pushl %ecx
    pushl %edx
    jmp _read
    