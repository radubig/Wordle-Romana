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
    jge B_err
        pushl $ERR_MSG
        call _stderr
        call _exit
    B_err:
    
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

# Description
#    Writes data to stdout (fixed size)
# Usage:
#    pushl *[data]
#    pushl size
#    call _stdout_sz
.data
    _rip_4: .space 4
    p_data_4: .space 4
    p_size_4: .long 0
.text
.global _stdout_sz
_stdout_sz:
    # Function header
    popl _rip_4
    popl p_size_4
    popl p_data_4

    pushal
        movl $4, %eax # syscall 4: write
        movl $1, %ebx # file_descriptor
        movl p_data_4, %ecx # data
        movl p_size_4, %edx # length
        int $0x80
    popal

    # Function footer
    pushl _rip_4
    ret


# Description
#    Writes an integer to a file descriptor, followed by a newline.
# Usage:
#    pushl [file_descriptor]
#    pushl [value]
#    call _write_int
.data
    _rip_5: .space 4
    val_5: .space 4
    fd_5: .space 4
    sz_5: .long 0
    buf_rev: .space 12
    buf_fwd: .space 12
.text
.global _write_int
_write_int:
    popl _rip_5
    popl val_5
    popl fd_5

    pushal
        # Load the number in reverse
        movl val_5, %eax
        xorl %edx, %edx
        xorl %ecx, %ecx
        lea buf_rev, %edi
        movl $10, %ebx
        L_5:
            divl %ebx
            addl $48, %edx
            movb %dl, (%edi, %ecx, 1)
            xorl %edx, %edx
            incl %ecx
            cmp $0, %eax
            jne L_5

        movl %ecx, sz_5
        # Reverse the string
        decl %ecx
        xorl %eax, %eax
        lea buf_rev, %esi
        lea buf_fwd, %edi
        L_5_1:
            cmp sz_5, %eax
            jge L_5_2
            movb (%esi, %ecx, 1), %bl
            movb %bl, (%edi, %eax, 1)
            incl %eax
            decl %ecx
            jmp L_5_1

        L_5_2:
        # Add newline
        movl $10, %ebx
        movb %bl, (%edi, %eax, 1)
        incl sz_5

    popal

    # Write Data
    pushl fd_5
    pushl $buf_fwd
    pushl sz_5
    call _write_sz

    pushl _rip_5
    ret


# Description
#    Writes data to a file descriptor (fixed size)
# Usage:
#    pushl [file_descriptor]
#    pushl *[data]
#    pushl size
#    call _write_sz
.data
    _rip_6: .space 4
    p_data_6: .space 4
    p_size_6: .long 0
    fd_6: .long 0
.text
.global _write_sz
_write_sz:
    # Function header
    popl _rip_6
    popl p_size_6
    popl p_data_6
    popl fd_6

    pushal
        movl $4, %eax # syscall 4: write
        movl fd_6, %ebx # file_descriptor
        movl p_data_6, %ecx # data
        movl p_size_6, %edx # length
        int $0x80
    popal

    # Function footer
    pushl _rip_6
    ret
