# Description
#    Writes data to a file descriptor.
# Usage:
#    pushl *[data]
#    pushl [file_descriptor]
#    call _write
.data
    ERR_MSG: .asciz "A aparut o eroare la scrierea in fisier"
    
    rip: .space 4
    r_data: .space 4
    r_fd: .space 4
    r_length: .space 4
.text
.global _write
_write:
    # Function header
    popl rip
    popl r_fd
    popl r_data

    # Calculate data length
    pushl r_data
    call string__length
    popl r_length

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal    
        movl $4, %eax # syscall 4: write
        movl r_fd, %ebx # file_descriptor
        movl r_data, %ecx # data
        movl r_length, %edx # length
        int $0x80
        movl %eax, r_length
        popal
    ## End register block
    
    # Catch and throw any errors
    cmpl $0, r_length
    jge _write__if_ERR
        pushl $ERR_MSG
        call _stderr
        call _exit
    _write__if_ERR:
    
    # Function footer
    pushl rip
    ret

# Description
#    Writes data to stdout.
# Usage:
#    pushl *[data]
#    call _stdout
.data
    rip_2: .space 4
    r_data_2: .space 4
.text
.global _stdout
_stdout:
    # Function header
    popl rip_2
    popl r_data_2

    # Call _write function with stdout as file_descriptor parameter
    pushl r_data_2
    pushl $1 # stdout
    call _write

    # Function footer    
    pushl rip_2
    ret

# Description
#    Writes data to stderr.
# Usage:
#    pushl *[data]
#    call _stderr
.data
    rip_3: .space 4
    r_data_3: .space 4
.text
.global _stderr
_stderr:
    # Function header
    popl rip_3
    popl r_data_3

    # Call _write function with stderr as file_descriptor parameter
    pushl r_data_3
    pushl $2 # stderr
    call _write

    # Function footer    
    pushl rip_3
    ret
