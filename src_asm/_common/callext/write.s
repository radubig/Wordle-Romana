.text

.global _write
_write:
    popl %ecx # rip
    popl %edx # data
    pushl %ecx

    movl $4, %eax # syscall 4: write
    movl $1, %ebx # file: stdout
    movl %edx, %ecx # data 
    call auto_str_len # data_len
    int $0x80
    
    ret

auto_str_len:
    movl $1, %edx
    
    auto_str_len__for1:
        add $1, %edx
        cmpb $0, (%ecx, %edx, 1)
        jne auto_str_len__for1

    ret
