.data
    ERR_MSG: .asciz "A aparut o eroare la generarea aleatorie\n"
    rnd_num: .space 4

    rip: .space 4
    r1: .space 4
    r2: .space 4
    r3: .space 4
    r4: .space 4
.text

# Description:
#     Generates a 32-bit random number.
# Usage:
#     call _getrandom
#     popl [32_bit_rnd]
.global _getrandom
_getrandom:
    popl rip
    pushal

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
    
    popal
    pushl rnd_num
    pushl rip
    ret
