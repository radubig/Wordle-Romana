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
    
    _rip: .space 4
    p_fd: .space 4
    p_buffer: .space 4
    r_length: .space 4
.text
.global _read
_read:
    # Function header
    popl _rip
    popl r_length
    popl p_buffer
    popl p_fd

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $3, %eax # syscall 3: read
        movl p_fd, %ebx # file_descriptor
        movl p_buffer, %ecx # buffer
        movl r_length, %edx # max_length
        int $0x80
        movl %eax, r_length
        popal
    ## End register block
    
    # Catch and throw any errors
    cmpl $0, r_length
    jge B_err
        pushl $ERR_MSG
        call _stderr
        call _exit
    B_err:
    
    # Function footer
    pushl r_length # return value (length)
    pushl _rip
    ret

# Description
#    Reads data up to the specified length from stdin and returns the actual length of the data.
# Usage:
#     pushl *[buffer]
#     pushl [max_length]
#     call _stdin
#     popl [length]
.data
    _rip_2: .space 4
    p_buffer_2: .space 4
    r_length_2: .space 4
.text
.global _stdin
_stdin:
    # Function header
    popl _rip_2
    popl r_length_2
    popl p_buffer_2
    
    # Call _read function with stdin as file_descriptor parameter
    pushl $0 # stdin
    pushl p_buffer_2
    pushl r_length_2
    call _read
    popl r_length_2
    
    # Function footer
    pushl r_length_2 # return value (length)
    pushl _rip_2
    ret


# Description:
#    Reads data from a file descriptor and returns the integer value.
#    This function is only meant to be used for positive numbers up to 3 digits. (Max lenght will be auto-set accordingly)
# Usage:
#    pushl [file_descriptor]
#    pushl *[buffer]
#    call _read_int
#    popl [value]
.data
    r3_rip: .space 4
    r3_fd: .space 4
    r3_buf: .space 4
    r3_value: .long 0
    r3_sz: .long 0
.text
.global _read_int
_read_int:
    popl r3_rip
    popl r3_buf
    popl r3_fd
    movl $0, r3_value

    pushal
        # Call read
        pushl r3_fd
        pushl r3_buf
        pushl $3
        call _read
        popl r3_sz

        xorl %eax, %eax
        xorl %ecx, %ecx
        xorl %edx, %edx
        movl r3_buf, %esi

        R3_LOOP:
        cmp r3_sz, %ecx
        jge R3_FIN
        xorl %ebx, %ebx
        movb (%esi, %ecx, 1), %bl
        cmp $48, %ebx # %ebx < '0' ?
        jl R3_FIN
        cmp $57, %ebx # %ebx > '9' ?
        jg R3_FIN
        movl $10, %edx
        mul %edx
        subl $48, %ebx
        addl %ebx, %eax
        incl %ecx
        jmp R3_LOOP

        R3_FIN:
        movl %eax, r3_value
    popal

    pushl r3_value
    pushl r3_rip
    ret
