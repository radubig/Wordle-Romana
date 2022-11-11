# Description:
#     Returns the absolute value of a number
# Usage:
#     pushl [num]
#     call math__abs
#     popl [num_abs]
.data
    _rip: .space 4
    p_num: .space 4
    r_abs: .space 4
.text
.global math__abs
math__abs:
    # Function header
    popl _rip
    popl p_num
    
    ## Begin register block: %ecx, %edx
        pushal
        movl p_num, %edx
    
        mov %edx, %ecx
        neg %edx
        cmovl %ecx, %edx
    
        mov %edx, r_abs
        popal
    ## End register block
    
    # Function footer
    pushl r_abs # return value (num_abs)
    pushl _rip
    ret
