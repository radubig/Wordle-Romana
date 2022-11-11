# Description
#    Writes data to a file descriptor.
# Usage:
#    pushl [file_descriptor]
#    pushl *[data]
#    call _write
.data
    ERR_MSG: .asciz "A aparut o eroare la scrierea in fisier"
    
    _rip: .space 4
    p_fd: .space 4
    p_data: .space 4
    l_length: .space 4
.text
.global _write
_write:
    # Function header
    popl _rip
    popl p_data
    popl p_fd

    # Calculate data length
    pushl p_data
    call string__length
    popl l_length

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $4, %eax # syscall 4: write
        movl p_fd, %ebx # file_descriptor
        movl p_data, %ecx # data
        movl l_length, %edx # length
        int $0x80
        movl %eax, l_length
        popal
    ## End register block
    
    # Catch and throw any errors
    cmpl $0, l_length
    jge _write__if_ERR
        pushl $ERR_MSG
        call _stderr
        call _exit
    _write__if_ERR:
    
    # Function footer
    pushl _rip
    ret

# Description
#    Writes data to stdout.
# Usage:
#    pushl *[data]
#    call _stdout
.data
    _rip_2: .space 4
    p_data_2: .space 4
.text
.global _stdout
_stdout:
    # Function header
    popl _rip_2
    popl p_data_2

    # Call _write function with stdout as file_descriptor parameter
    pushl $1 # stdout
    pushl p_data_2
    call _write

    # Function footer    
    pushl _rip_2
    ret

# Description
#    Writes data to stderr.
# Usage:
#    pushl *[data]
#    call _stderr
.data
    _rip_3: .space 4
    p_data_3: .space 4
.text
.global _stderr
_stderr:
    # Function header
    popl _rip_3
    popl p_data_3

    # Call _write function with stderr as file_descriptor parameter
    pushl $2 # stderr
    pushl p_data_3
    call _write

    # Function footer    
    pushl _rip_3
    ret
