# Wrapper around write syscall
# Usage:
#    pushl [data]
#    pushl [file_descriptor]
#    call _write
# or
#    pushl [data]
#    call _stdout
# or
#    pushl [data]
#    call _stderr

.data

ERR_MSG_1: .asciz "A aparut o eroare la citirea din fisierul "
ERR_MSG_2: .asciz "\n"

.text

.global _write
_write:
    popl %edx # rip
    popl %ebx # file_descriptor
    popl %ecx # data
    pushl %edx

    movl $4, %eax # syscall 4: write
    # %ebx (file_descriptor) is popped from stack
    # %ecx (data) is popped from stack
    call auto_str_len # data_len
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

.global _stdout
_stdout:
    popl %edx # rip
    pushl $1 # stdout
    pushl %edx
    jmp _write

.global _stderr
_stderr:
    popl %edx # rip
    pushl $2 # stderr
    pushl %edx
    jmp _write

auto_str_len:
    movl $0, %edx
    
    auto_str_len__for1:
        add $1, %edx
        cmpb $0, (%ecx, %edx, 1)
        jne auto_str_len__for1

    ret
