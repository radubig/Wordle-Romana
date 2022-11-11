# Description:
#     Generates a 32-bit random number.
# Usage:
#     call _getrandom
#     popl [32_bit_rnd]
.data
    ERR_MSG: .asciz "A aparut o eroare la generarea aleatorie\n"
    
    rip: .space 4
    r_rndnum: .space 4
    r_length: .space 4
.text
.global _getrandom
_getrandom:
    # Function header
    popl rip

    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $0x163, %eax # syscall 355: getrandom
        movl $r_rndnum, %ebx # buffer
        movl $4, %ecx # length
        movl $0, %edx # flags
        int $0x80
        movl %eax, r_length # output_length
        popal
    ## End register block

    # Catch and throw any errors
    cmpl $0, r_length
    jge _getrandom__if_ERR
        pushl $ERR_MSG
        call _stderr
        call _exit
    _getrandom__if_ERR:
    
    # Function footer
    pushl r_rndnum # return value (32_bit_rnd)
    pushl rip
    ret
