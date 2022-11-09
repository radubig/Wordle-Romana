.data
    ERR_MSG: .asciz "A aparut o eroare la generarea aleatorie\n"
    rnd_num: .space 4

.text

.global _getrandom
_getrandom:
    movl $0x163, %eax # syscall 355: getrandom
    movl $rnd_num, %ebx # buffer
    movl $4, %ecx # length
    movl $0, %edx # flags
    int $0x80

    cmpl $0, %eax # catch error
    jge _getrandom__if_ERR
        pushl $ERR_MSG
        call _stderr
        
        call _exit
    _getrandom__if_ERR:
    
    popl %eax
    pushl rnd_num
    pushl %eax
    
    ret