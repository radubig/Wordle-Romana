# Description:
#    Opens a file.
# Usage:
#    pushl *[file_name]
#    call _open
#    popl [file_descriptor]
.data
    ERR_MSG_1: .asciz "A aparut o eroare la deschiderea fisierului "
    ERR_MSG_2: .asciz "\n"

    _rip: .space 4
    p_filename: .space 4
    r_fd: .space 4
.text
.global _open
_open:
    # Function header
    popl _rip
    popl p_filename
    
    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $5, %eax # syscall 5: open
        movl p_filename, %ebx # file_name
        movl $0, %ecx # O_RDONLY (read only)
        movl $0, %edx # ignored for O_RDONLY
        int $0x80
        movl %eax, r_fd # file_descriptor
        popal
    ## End register block

    # Catch and throw any errors
    cmpl $0, r_fd
    jge B_err
        pushl $ERR_MSG_1
        call _stderr
        pushl p_filename
        call _stderr
        pushl $ERR_MSG_2
        call _stderr
        call _exit
    B_err:

    # Function footers
    pushl r_fd # return value (file_descriptor)
    pushl _rip
    ret


# Description:
#    Closes a file.
# Usage:
#    pushl [file_descriptor]
#    call _close
.data
    _rip_2: .space 4
    p_fd_2: .space 4
.text
.global _close
_close:
    popl _rip_2
    popl p_fd_2

    pushal
        movl $0x06, %eax # 6: close
        movl p_fd_2, %ebx
        int $0x80
    popal

    pushl _rip_2
    ret


# Description:
#    Opens a file for writing (and creates it if it doesn't exist)
# Usage:
#    pushl *[file_name]
#    call _open_w
#    popl [file_descriptor]
.data
    ERR_MSG_1q: .asciz "A aparut o eroare la deschiderea fisierului "
    ERR_MSG_2q: .asciz "\n"

    _ripq: .space 4
    p_filenameq: .space 4
    r_fdq: .space 4
.text
.global _open_w
_open_w:
    # Function header
    popl _ripq
    popl p_filenameq

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $5, %eax # syscall 5: open
        movl p_filenameq, %ebx # file_name
        movl $0101, %ecx # O_RDONLY | O_CREAT
        movl $0666, %edx # idk
        int $0x80
        movl %eax, r_fdq # file_descriptor
        popal
    ## End register block

    # Catch and throw any errors
    cmpl $0, r_fdq
    jge B_errq
        pushl $ERR_MSG_1q
        call _stderr
        pushl p_filenameq
        call _stderr
        pushl $ERR_MSG_2q
        call _stderr
        call _exit
    B_errq:

    # Function footers
    pushl r_fdq # return value (file_descriptor)
    pushl _ripq
    ret
