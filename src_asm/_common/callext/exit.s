.text

.global _exit
_exit:
    popl %ecx

    movl $1, %eax # syscall 1: exit
    movl $0, %ebx # exitcode: 0
    int $0x80