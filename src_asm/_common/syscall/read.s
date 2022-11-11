# Description
#    Reads data up to the specified length from a file descriptor and returns the actual length of the data.
# Usage:
#    pushl [file_descriptor]
#    pushl *[buffer]
#    pushl [max_length]
#    call _read
#    popl [length]
.data
    ERR_MSG: .asciz "A aparut o eroare la citirea din fisier"
    
    rip: .space 4
    r_fd: .space 4
    r_buffer: .space 4
    r_length: .space 4
.text
.global _read
_read:
    # Function header
    popl rip
    popl r_length
    popl r_buffer
    popl r_fd

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $3, %eax # syscall 3: read
        movl r_fd, %ebx # file_descriptor
        movl r_buffer, %ecx # buffer
        movl r_length, %edx # max_length
        int $0x80
        movl %eax, r_length
        popal
    ## End register block
    
    # Catch and throw any errors
    cmpl $0, r_length
    jge _read__if_ERR
        pushl $ERR_MSG
        call _stderr
        call _exit
    _read__if_ERR:
    
    # Function footer
    pushl r_length # return value (length)
    pushl rip
    ret

# Description
#    Reads data up to the specified length from stdin and returns the actual length of the data.
# Usage:
#     pushl *[buffer]
#     pushl [max_length]
#     call _stdin
#     popl [length]
.data
    rip_2: .space 4
    r_buffer_2: .space 4
    r_length_2: .space 4
.text
.global _stdin
_stdin:
    # Function header
    popl rip_2
    popl r_length_2
    popl r_buffer_2
    
    # Call _read function with stdin as file_descriptor parameter
    pushl $0 # stdin
    pushl r_buffer_2
    pushl r_length_2
    call _read
    popl r_length_2
    
    # Function footer
    pushl r_length_2 # return value (length)
    pushl rip_2
    ret
